#include "file_reader.h"

DocumentList* read_index_file(char* dir) {
    char *file_path = malloc(strlen(dir) + strlen("index.txt") + 1);
    strcpy(file_path, dir);
    strcat(file_path, "index.txt");

    FILE* index_file = fopen(file_path, "r");
    if (index_file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    DocumentList* list = document_list_create(2);

    char* line = NULL;
    size_t len = 0;
    
    while (getline(&line, &len, index_file) != -1) {
        // Remover o caractere de nova linha, se estiver presente
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
        }

        document_list_add(list, document_create(string_create(line)));
    }

    free(line);  // Liberar a memória alocada para a linha
    free(file_path);
    fclose(index_file);

    return list;
}

/*
Formato do arquivo:
<doc_name:string> <n:int> <doc1> <doc2> ... <docn>

*/
void read_graph_file(char* dir, DocumentList* list) {
    char *file_path = malloc(strlen(dir) + strlen("graph.txt") + 1);
    strcpy(file_path, dir);
    strcat(file_path, "graph.txt");

    FILE* graph_file = fopen(file_path, "r");
    if (graph_file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char* line = NULL;
    size_t len = 0;
    String* temp = string_create("");
    
    while (getline(&line, &len, graph_file) != -1) {
        // Remover o caractere de nova linha, se estiver presente
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
        }


        char* doc_name = strtok(line, " ");
        char* n_str = strtok(NULL, " ");
        int n = atoi(n_str);

        string_set(temp, doc_name);
        Document* doc = document_list_get(list, document_list_binary_search(list, temp));

        for (int i = 0; i < n; i++) {
            char* doc_name = strtok(NULL, " ");

            string_set(temp, doc_name);
            document_link_to(doc, document_list_get(list, document_list_binary_search(list, temp)));
        }
    }

    string_destroy(temp);
    free(line);  // Liberar a memória alocada para a linha
    free(file_path);
    fclose(graph_file);
}

SymbolTable* read_stopwords_file(char* dir) {
    char *file_path = malloc(strlen(dir) + strlen("stopwords.txt") + 1);
    strcpy(file_path, dir);
    strcat(file_path, "stopwords.txt");

    FILE* stopword_file = fopen(file_path, "r");
    if (stopword_file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    SymbolTable *sw = symbol_table_init(NULL, NULL, (void (*)(void *))free);

    char* line = NULL;
    size_t len = 0;

    // String auxiliar para armazenar a palavra
    String *temp = string_create("");
    while (getline(&line, &len, stopword_file) != -1) {
        // Remover o caractere de nova linha, se estiver presente
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
        }

        // Armazenar a palavra na string auxiliar
        string_set(temp, line);

        // O valor não importa, pois não será usado, apenas a chave, para indicar que a palavra é uma stopword
        symbol_table_put(sw, temp, (unsigned char *)malloc(sizeof(unsigned char)));
    }

    string_destroy(temp);
    free(line);  // Liberar a memória alocada para a linha
    free(file_path);
    fclose(stopword_file);

    return sw;
}

SymbolTable *read_page_file(char *dir, DocumentList *list, SymbolTable *stopwords) {
    SymbolTable *symbol_table = symbol_table_init(NULL, NULL, (void (*)(void *))linked_list_destroy);

    String *word = string_create("");
    for (int i = document_list_get_size(list) - 1; i >= 0; i--) {
        // Cria uma tabela de símbolos para armazenar as palavras já lidas neste documento
        SymbolTable *history = symbol_table_init(NULL, NULL, (void (*)(void *))free);

        Document *current_doc = document_list_get(list, i);
        String *string_doc_name = document_get_name(current_doc);

        char* doc_name = get_char_pointer_from_string(string_doc_name);
        char *file_path = malloc(strlen(dir) + strlen("pages/") + strlen(doc_name) + 1);

        strcpy(file_path, dir);
        strcat(file_path, "pages/");
        strcat(file_path, doc_name);

        FILE *page_file = fopen(file_path, "r");
        if (page_file == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }

        char buffer[256];
        while (fscanf(page_file, "%255s", buffer) == 1) {
            char *token = strtok(buffer, " \t\n");
            while (token != NULL) {
                for (int j = 0; token[j]; j++) {
                    token[j] = tolower(token[j]);
                }

                string_set(word, token);
                if(!symbol_table_contains(stopwords, word) && !symbol_table_contains(history, word)) {

                    LinkedList *doc_list = symbol_table_get(symbol_table, word);
                    if (doc_list == NULL) {
                        doc_list = linked_list_construct();
                        linked_list_push_front(doc_list, current_doc);
                        symbol_table_put(symbol_table, word, doc_list);
                    }
                    else {
                        linked_list_push_front(doc_list, current_doc);
                    }

                    symbol_table_put(history, word, (unsigned char *)malloc(sizeof(unsigned char)));
                }

                token = strtok(NULL, " \t\n");
            }
        }

        fclose(page_file);
        free(file_path);
        symbol_table_destroy(history);
    }
    string_destroy(word);


    return symbol_table;
}
