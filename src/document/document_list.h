#ifndef DOCUMENT_LIST_H
#define DOCUMENT_LIST_H

#include "document.h"
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma lista de documentos
typedef struct {
    Document **docs;
    int size;
    int capacity;
} DocumentList;

/// @brief Cria uma nova lista de documentos com capacidade inicial
/// @param capacity - Capacidade inicial da lista
/// @return DocumentList - Um ponteiro para uma nova lista de documentos
DocumentList *document_list_create(int capacity);

/// @brief Destrói uma lista de documentos, liberando a memória associada
/// @param list - A lista de documentos a ser destruída
void document_list_destroy(DocumentList *list);

/// @brief Obtém o documento na posição especificada na lista
/// @param list - A lista de documentos
/// @param index - A posição do documento na lista
/// @return Document - O documento na posição especificada
Document *document_list_get(DocumentList *list, int index);

/// @brief Adiciona um documento à lista
/// @param list - A lista de documentos
/// @param doc - O documento a ser adicionado
void document_list_add(DocumentList *list, Document *doc);

/// @brief Obtém o tamanho atual da lista de documentos
/// @param list - A lista de documentos
/// @return int - O tamanho da lista de documentos
int document_list_get_size(DocumentList *list);

/// @brief Ordena a lista de documentos
/// @param list - A lista de documentos a ser ordenada
void document_list_sort(DocumentList *list);

/// @brief Realiza uma busca binária na lista de documentos com base no nome do documento
/// @param list - A lista de documentos ordenada
/// @param name - O nome do documento a ser buscado
/// @return Document - O documento encontrado ou NULL caso não seja encontrado
int document_list_binary_search(DocumentList *list, String *name);

/// @brief Obtém o índice de um documento em uma lista de documentos
/// @param list - A lista de documentos
/// @param doc - O documento
/// @return int - O índice do documento na lista, ou -1 caso não esteja na lista
int document_list_index_of(DocumentList *list, Document *doc);

void document_list_print(DocumentList *list);

#endif // DOCUMENT_LIST_H
