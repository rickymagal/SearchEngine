#include "page_rank.h"

PageRank *page_rank_create(DocumentList *documents) {
    PageRank *page_rank = malloc(sizeof(PageRank));
    page_rank->documents = documents;
    page_rank->ranks = malloc(sizeof(double) * document_list_get_size(documents));
    for(int i = 0; i < document_list_get_size(documents); i++) {
        page_rank->ranks[i] = 1.0 / document_list_get_size(documents);
    }
    return page_rank;
}

void page_rank_destroy(PageRank *page_rank) {
    free(page_rank->ranks);
    free(page_rank);
}

double threshold(int n, double *ranks, double *new_ranks) {
    double E = 0;
    for(int i = 0; i < n; i++) {
        E += fabs(new_ranks[i] - ranks[i]);
    }
    return (1.0/n) * E;
}

void show_iteration(int i, int n, double E, double *ranks) {
    printf("Iteração %d: E = %lf Rank: [", i, E);
    for(int i = 0; i < n; i++) {
        printf("%lf", ranks[i]);
        if(i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void page_rank_calculate_ranks(PageRank *page_rank) {
    int n = document_list_get_size(page_rank->documents); // Número de documentos
    double *ranks = page_rank->ranks; // PR(k−1)(i)
    double *new_ranks = malloc(sizeof(double) * n); // PR(k)(i)
    double E = 1; // E(k)
    while(E >= THRESHOLD) { // Enquanto E(k) > epsilon
        for(int i = 0; i < n; i++) { // Para cada página i
            double sum = 0; // Somatório
            Document *doc = document_list_get(page_rank->documents, i); // Página i
            LinkedList *in = document_get_in(doc); // Páginas que apontam para i

            Node *node = linked_list_get_head(in);
            while(node != NULL) {
                Document *in_doc = node_get_data(node);
                int size = document_get_out_size(in_doc);
                sum += ranks[document_list_index_of(page_rank->documents, in_doc)] / size;
                node = node_get_next(node);
            }

            sum *= DAMPING_FACTOR; // Multiplica pelo fator de amortecimento (Ambos os casos da equação 3)

            // Caso especial 1 (i aponta para alguém) |Out(i)| != 0
            if(document_get_out_size(doc) != 0) {
                new_ranks[i] = (1 - DAMPING_FACTOR) / n + sum;
            }
            // Caso especial 2 (i não aponta para ninguém) |Out(i)| = 0
            else {
                new_ranks[i] = (1 - DAMPING_FACTOR) / n + DAMPING_FACTOR * ranks[i] + sum;
            }
        }
        E = threshold(n, ranks, new_ranks);
        memcpy(ranks, new_ranks, sizeof(double) * n);
    }
    free(new_ranks);
}

double page_rank_get_rank(PageRank *page_rank, int index) {
    return page_rank->ranks[index];
}

void page_rank_set_ranks(PageRank *page_rank) {
    for(int i = 0; i < document_list_get_size(page_rank->documents); i++) {
        Document *doc = document_list_get(page_rank->documents, i);
        document_set_rank(doc, page_rank_get_rank(page_rank, i));
    }
}

void page_rank_print(PageRank *page_rank) {
    for(int i = 0; i < document_list_get_size(page_rank->documents); i++) {
        Document *doc = document_list_get(page_rank->documents, i);
        string_show(document_get_name(doc));
        printf(" - %.19lf ", page_rank_get_rank(page_rank, i));
    }
}
