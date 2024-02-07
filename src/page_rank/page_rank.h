#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include <math.h>
#include <stdlib.h>
#include "../document/document_list.h"

#define DAMPING_FACTOR 0.85 // Fator de amortecimento [0, 1]
#define THRESHOLD 1e-6 // Limiar de convergência

typedef struct {
    DocumentList *documents; // Lista de documentos, onde documents[i] é o documento com rank ranks[i]
    double *ranks; // Vetor de ranks, onde ranks[i] é o rank do documento documents[i]
} PageRank;

/// @brief Cria uma nova estrutura de PageRank
/// @param documents - A lista de documentos
/// @return PageRank - Um ponteiro para uma nova estrutura de PageRank
PageRank *page_rank_create(DocumentList *documents);

/// @brief Destrói uma estrutura de PageRank, liberando a memória associada
/// @param page_rank - A estrutura de PageRank a ser destruída
void page_rank_destroy(PageRank *page_rank);

/// @brief Calcula o rank de cada documento
/// @param page_rank - A estrutura de PageRank
void page_rank_calculate_ranks(PageRank *page_rank);

void page_rank_set_ranks(PageRank *page_rank);

/// @brief Obtém o rank de um documento
/// @param page_rank - A estrutura de PageRank
/// @param index - O índice do documento
/// @return double - O rank do documento
double page_rank_get_rank(PageRank *page_rank, int index);

/// @brief Imprime os ranks de cada documento
/// @param page_rank - A estrutura de PageRank
void page_rank_print(PageRank *page_rank);

#endif // PAGE_RANK_H