#include "search_engine.h"

struct search_engine {
    SymbolTable *word_to_documents;
};

SearchEngine *search_engine_create(SymbolTable *pages) {
    SearchEngine *search_engine = malloc(sizeof(SearchEngine));
    search_engine->word_to_documents = pages;
    return search_engine;
}

void search_engine_destroy(SearchEngine *search_engine) {
    free(search_engine);
}

void node_print(Node *node) {
    if(node == NULL) {
        printf("null");
        return;
    }
    Document *d = node_get_data(node);
    document_print(d);
}

int node_document_compare(Node *a, Node *b) {
    Document *doc_a = node_get_data(a);
    Document *doc_b = node_get_data(b);
    return document_compare(&doc_a, &doc_b);
}

// Pega a interseção das N ocorrencias de uma palavra (Sabendo que a linked list está ordenada)
Vector *search_engine_search(SearchEngine *search_engine, Vector *words) {
    Vector *intersection = vector_new(2);

    // Cria um vetor de listas de documentos, para armazenar as listas de documentos de cada palavra
    Vector *nodes = vector_new(vector_get_size(words));

    // Para cada palavra da query
    for (size_t i = 0; i < vector_get_size(words); i++) {
        String *word = vector_at(words, i);

        // Busca a palavra na tabela de símbolos
        LinkedList *documents_list = symbol_table_get(search_engine->word_to_documents, word);

        // Se a palavra não estiver na tabela de símbolos, retorna uma lista vazia
        if(documents_list == NULL) {
            vector_destroy(nodes, NULL);
            return intersection;
        }
        // printf("word: "); string_show(word); printf("\n");
        // linked_list_print(documents_list, (void (*)(void *))document_print); printf("\n");

        // Adiciona a lista de documentos da palavra no vetor de listas de documentos
        vector_push_back(nodes, linked_list_get_head(documents_list));
    }

    // printf("\n\n");
    // vector_print(nodes, (void (*)(void *))node_print);
    
    while(!vector_contains_null(nodes)) {
        Node *max = vector_at(nodes, 0);
        for(size_t i = 1; i < vector_get_size(nodes); i++) {
            Node *current = vector_at(nodes, i);
            
            if(node_document_compare(current, max) > 0) {
                max = current;
            }
        }

        size_t cont_intersections = 0;
        for(size_t i = 0; i < vector_get_size(nodes); i++) {
            Node *current = vector_at(nodes, i);

            if(node_document_compare(current, max) == 0) {
                cont_intersections++;
                continue;
            }

            if(node_document_compare(current, max) < 0) {
                Node *next = node_get_next(current);
                vector_insert_at(nodes, i, next);
            }
            
        }

        if(cont_intersections == vector_get_size(nodes)) {
            vector_push_back(intersection, node_get_data(max));
            for(size_t i = 0; i < vector_get_size(nodes); i++) {
                Node *current = vector_at(nodes, i);
                Node *next = node_get_next(current);
                vector_insert_at(nodes, i, next);
            }
        }

        // vector_print(nodes, (void (*)(void *))node_print);
    }
    // printf("\n\n");

    // Ordena a lista de interseção, para que os documentos mais relevantes fiquem no início, caso o rank seja o mesmo, ordena por ordem alfabética
    vector_sort(intersection, document_compare_with_rank);

    vector_destroy(nodes, NULL);
    return intersection;
}

/*
Format:
word1 word2 word3
word1 word2
word1 word2 word3 word4
...
word1 word2 word3 word4 word5 word6 word7 word8 word9 word10
*/

void search_engine_query_from_file(SearchEngine *search_engine, char *dir) {
    char *file_path = malloc(strlen(dir) + strlen("searches.txt") + 1);

    strcpy(file_path, dir);
    strcat(file_path, "searches.txt");

    FILE *file = fopen(file_path, "r");
    if(file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", file_path);
        return;
    }

    //fscanf(file, "%255s", buffer) == 1

    // Cada linha do arquivo é uma query
    char buffer[256];
    while(fgets(buffer, 256, file) != NULL) {
        // Separa as palavras da query
        char *token = strtok(buffer, " \n");
        int words_count = 0;
        Vector *words = vector_new(2);
        while(token != NULL) {
            if(strlen(token) > 0)
                vector_push_back(words, string_create(token));
            token = strtok(NULL, " \n");
        }

        vector_print(words, (void (*)(void *))string_show);

        Vector *results = search_engine_search(search_engine, words);

        vector_print(results, (void (*)(void *))document_print);

        printf("\n");

        vector_destroy(results, NULL);
        vector_destroy(words, (void (*)(void *))string_destroy);
    }

    free(file_path);
    fclose(file);
}

//fgets(buffer, 256, stdin) != NULL

void search_engine_query_from_terminal(SearchEngine *search_engine) {
    char buffer[256];
    while(fgets(buffer, 256, stdin) != NULL) {
        // Separa as palavras da query
        char *token = strtok(buffer, " \n");
        int words_count = 0;
        Vector *words = vector_new(2);
        while(token != NULL) {
            if(strlen(token) > 0)
                vector_push_back(words, string_create(token));
            token = strtok(NULL, " \n");
        }

        Vector *results = search_engine_search(search_engine, words);

        // Imprime a query
        printf("search:");
        for (size_t i = 0; i < vector_get_size(words); i++) {
            string_show(vector_at(words, i));
            if(i != vector_get_size(words) - 1)
                printf(" ");
        }
        printf("\npages:");

        // Imprime os resultados
        for (size_t i = 0; i < vector_get_size(results); i++) {
            Document *doc = vector_at(results, i);
            string_show(document_get_name(doc));
            if(i != vector_get_size(results) - 1)
                printf(" ");
        }

        printf("\npr:");
        for (size_t i = 0; i < vector_get_size(results); i++) {
            Document *doc = vector_at(results, i);
            printf("%.16lf", doc->rank);
            if(i != vector_get_size(results) - 1)
                printf(" ");
        }
        printf("\n");

        vector_destroy(results, NULL);
        vector_destroy(words, (void (*)(void *))string_destroy);
    }
}

