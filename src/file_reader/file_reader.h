#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../document/document_list.h"
#include "../symbol_table/symbol_table.h"
#include "../linked_list/linked_list.h"
#include "../document/document.h"
#include "../string/string.h"


/**
 * @brief Realiza a leitura do arquivo index.txt
 * 
 * @param dir Caminho do diretório onde está o arquivo
 * @return Nova DocumentList
 */
DocumentList* read_index_file(char* dir);

/**
 * @brief Realiza a leitura do arquivo graph.txt
 * 
 * @param dir Caminho do diretório onde está o arquivo
 * @param list Lista com os documentos analisados
 */
void read_graph_file(char* dir, DocumentList* list);

/**
 * @brief Realiza a leitura do arquivo stopwords.txt
 * 
 * @param dir Caminho do diretório onde está o arquivo
 * @return Symbol table com as stopwords
 */
SymbolTable* read_stopwords_file(char* dir);

/**
 * @brief Realiza a leitura do de cada documento presente na pasta "pages/"
 * 
 * @param dir Caminho do diretório onde está a pasta
 * @param list Lista com os documentos analisados
 * @param stopwords Symbol table com as stopwords 
 * @return Nova symbol table com as palavras lidas nos documentos
 */
SymbolTable *read_page_file(char *dir, DocumentList *list, SymbolTable *stopwords);

#endif // FILE_READER_H
