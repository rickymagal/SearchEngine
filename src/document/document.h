#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <stdlib.h>
#include "../string/string.h"
#include "../linked_list/linked_list.h"

// Estrutura para representar um documento
typedef struct document {
    String *name;         // Nome do documento
    double rank;          // Rank do documento
    LinkedList *In;       // Lista de documentos que apontam para este
    LinkedList *Out;      // Lista de documentos que este aponta
} Document;

/// @brief Cria um novo documento
/// @param name - O nome do documento
/// @return Document - Um ponteiro para um novo objeto Document
Document *document_create(String *name);

/// @brief Destrói um documento
/// @param doc - O documento a ser destruído
void document_destroy(Document *doc);

void document_set_rank(Document *doc, double rank);

/// @brief Obtém o nome do documento
/// @param doc - O documento
/// @return String - O nome do documento
String *document_get_name(Document *doc);

/// @brief Obtém a lista de documentos que apontam para este documento
/// @param doc - O documento
/// @return LinkedList - A lista de documentos que apontam para este
LinkedList *document_get_in(Document *doc);

/// @brief Obtém a lista de documentos que este documento aponta
/// @param doc - O documento
/// @return LinkedList - A lista de documentos que este aponta
LinkedList *document_get_out(Document *doc);

/// @brief Adiciona um documento de entrada para este documento
/// @param doc - O documento de destino
/// @param in - O documento de entrada
void document_add_in(Document *doc, Document *in);

/// @brief Adiciona um documento de saída para este documento
/// @param doc - O documento de origem
/// @param out - O documento de saída
void document_add_out(Document *doc, Document *out);

/// @brief Adiciona um link entre dois documentos
/// @param doc - O documento de origem
/// @param to - O documento de destino
void document_link_to(Document *doc, Document *to);

/// @brief Obtém o número de documentos de entrada para este documento
/// @param doc - O documento
/// @return int - O número de documentos de entrada
int document_get_in_size(Document *doc);

/// @brief Obtém o número de documentos de saída deste documento
/// @param doc - O documento
/// @return int - O número de documentos de saída
int document_get_out_size(Document *doc);

/// @brief Compara dois documentos para ordenação
/// @param a - O primeiro documento
/// @param b - O segundo documento
/// @return int - Resultado da comparação
int document_compare(const void *a, const void *b);

/// @brief Compara dois documentos para ordenação por rank
/// @param a - O primeiro documento
/// @param b - O segundo documento
/// @return int - Resultado da comparação
int document_compare_with_rank(const void *a, const void *b);

/// @brief Retorna o tamanho da estrutura Document
/// @return size_t - Tamanho da estrutura Document
size_t document_sizeof();

/// @brief Imprime um documento
/// @param doc - O documento
void document_print(Document *doc);

#endif // DOCUMENT_H