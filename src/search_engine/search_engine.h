#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../vector/vector.h"
#include "../types.h"
#include "../symbol_table/symbol_table.h"
#include "../linked_list/linked_list.h"
#include "../document/document.h"
#include "../document/document_list.h"

typedef struct search_engine SearchEngine;


/**
 * @brief Cria uma search engine
 * 
 * @param pages Symbol table com as palavras presentes nos documentos 
 * @return Nova search engine
 */
SearchEngine *search_engine_create(SymbolTable *pages);

/**
 * @brief Libera a memória alocada pela search engine
 * 
 * @param search_engine Search engine a ser destruída
 */
void search_engine_destroy(SearchEngine *search_engine);

/**
 * @brief Acha a interseção das ocorrências de um grupo de palavras
 * 
 * @param search_engine Search engine 
 * @param words Palavras analisadas
 * @return Vector* com os documentos da interseção
 */
Vector *search_engine_search(SearchEngine *search_engine, Vector *words);

/**
 * @brief Realiza a pesquisa a partir de um arquivo
 * 
 * @param search_engine Search engine
 * @param dir Caminho do diretório onde está o arquivo
 */
void search_engine_query_from_file(SearchEngine *search_engine, char *dir);

/**
 * @brief Realiza a pesquisa a partir da leitura da entrada padrão
 * 
 * @param search_engine Search engine
 */
void search_engine_query_from_terminal(SearchEngine *search_engine);


#endif // SEARCH_ENGINE_H