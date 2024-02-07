#include <stdio.h>
#include <stdlib.h>
#include "src/string/string.h"
#include "src/linked_list/linked_list.h"
#include "src/vector/vector.h"
#include "src/node/node.h"
#include "src/document/document.h"
#include "src/document/document_list.h"
#include "src/file_reader/file_reader.h"
#include "src/page_rank/page_rank.h"
#include "src/search_engine/search_engine.h"


void print_string(void* data) {
    String* str = (String*) data;
    string_show(str);
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <dir>\n", argv[0]);
        exit(1);
    }

    // Concatena '/' ao final do diretório, se não estiver presente
    if (argv[1][strlen(argv[1]) - 1] != '/') {
        char* temp = malloc(strlen(argv[1]) + 2);
        strcpy(temp, argv[1]);
        strcat(temp, "/");
        strcpy(argv[1], temp);
        free(temp);
    }

    // Lê os nomes dos documentos do arquivo de índice e os armazena na lista de documentos
    DocumentList *list = read_index_file(argv[1]);
    // Ordena a lista de documentos por ordem alfabética, para possibilitar a busca binária
    document_list_sort(list);

    // Lê os dados do arquivo de grafo e os armazena na lista de documentos
    read_graph_file(argv[1], list);

    // Cria a estrutura de dados para armazenar os ranks
    PageRank *page_rank = page_rank_create(list);

    // printf("\nCalculando ranks...\n\n");
    page_rank_calculate_ranks(page_rank);
    page_rank_set_ranks(page_rank);
    // page_rank_print(page_rank);

    // Lê as StorWords do arquivo e as armazena na lista de stop words
    SymbolTable *stopwords = read_stopwords_file(argv[1]);

    // Lê as palavras e mapeia para uma lista de documentos (Linked List)
    SymbolTable *pages = read_page_file(argv[1], list, stopwords);

    // Cria a ED responsavel por armazenar os dados do motor de busca
    SearchEngine *search_engine = search_engine_create(pages);

    // Realiza as queries do arquivo de busca
    // search_engine_query_from_file(search_engine, argv[1]);

    // Realiza as queries da entrada padrão
    search_engine_query_from_terminal(search_engine);

    // Libera a memória alocada
    search_engine_destroy(search_engine);
    symbol_table_destroy(pages);
    symbol_table_destroy(stopwords);
    page_rank_destroy(page_rank);
    document_list_destroy(list);
    return 0;
}
