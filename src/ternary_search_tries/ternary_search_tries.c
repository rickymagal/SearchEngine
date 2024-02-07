#include "ternary_search_tries.h"

typedef struct tst_node {
    Value val;
    unsigned char c;
    struct tst_node *l, *m, *r;
} TSTNode;

TSTNode *tst_node_create(unsigned char c, Value val, TSTNode *l, TSTNode *m, TSTNode *r) {
    TSTNode *node = (TSTNode *) malloc(sizeof(TSTNode));
    node->c = c;
    node->val = val;
    node->l = l;
    node->m = m;
    node->r = r;
    return node;
}

TSTNode *tst_node_destroy(TSTNode *node, DestroyFunction destroy_val) {
    if (node == NULL) return NULL;
    node->l = tst_node_destroy(node->l, destroy_val);
    node->m = tst_node_destroy(node->m, destroy_val);
    node->r = tst_node_destroy(node->r, destroy_val);
    if (node->val != NULL && destroy_val != NULL) {
        destroy_val(node->val);
    }
    free(node);
    return NULL;
}

struct ternary_search_tries {
    TSTNode *root;
    DestroyFunction destroy_val;
};

TernarySearchTries *tst_create(DestroyFunction destroy_val) {
    TernarySearchTries *tst = (TernarySearchTries *) malloc(sizeof(TernarySearchTries));
    tst->root = NULL;
    tst->destroy_val = destroy_val;
    return tst;
}

void tst_destroy(TernarySearchTries *tst) {
    tst->root = tst_node_destroy(tst->root, tst->destroy_val);
    free(tst);
}

TSTNode *aux_tst_insert(TSTNode *node, String *key, Value val, size_t d, DestroyFunction destroy_val) {
    unsigned char c = string_get_char_at(key, d);
    if (node == NULL) node = tst_node_create(c, NULL, NULL, NULL, NULL);
    if (c < node->c) node->l = aux_tst_insert(node->l, key, val, d, destroy_val);
    else if (c > node->c) node->r = aux_tst_insert(node->r, key, val, d, destroy_val);
    else if (d < string_get_length(key) - 1) node->m = aux_tst_insert(node->m, key, val, d + 1, destroy_val);
    else {
        if (node->val != NULL && destroy_val != NULL) destroy_val(node->val);
        node->val = val;
    }
    return node;
}

void tst_insert(TernarySearchTries *tst, String *key, Value val) {
    tst->root = aux_tst_insert(tst->root, key, val, 0, tst->destroy_val);
}

TSTNode *aux_tst_get(TSTNode *node, String *key, size_t d) {
    if (node == NULL) return NULL;
    unsigned char c = string_get_char_at(key, d);
    if (c < node->c) return aux_tst_get(node->l, key, d);
    else if (c > node->c) return aux_tst_get(node->r, key, d);
    else if (d < string_get_length(key) - 1) return aux_tst_get(node->m, key, d + 1);
    else return node;
}

Value tst_get(TernarySearchTries *tst, String *key) {
    TSTNode *node = aux_tst_get(tst->root, key, 0);
    if (node == NULL) return NULL;
    return node->val;
}

bool tst_node_exists(TSTNode *node, String *key, size_t d) {
    if (node == NULL) return false;
    unsigned char c = string_get_char_at(key, d);
    if (c < node->c) return tst_node_exists(node->l, key, d);
    else if (c > node->c) return tst_node_exists(node->r, key, d);
    else if (d < string_get_length(key) - 1) return tst_node_exists(node->m, key, d + 1);
    else return true;
}

bool tst_exists(TernarySearchTries *tst, String *key) {
    return tst_node_exists(tst->root, key, 0);
}

bool tst_contains(TernarySearchTries *tst, String *key) {
    return tst_get(tst, key) != NULL;
}

bool tst_is_empty(TernarySearchTries *tst) {
    return tst->root == NULL;
}


void tst_node_show(TSTNode *node, size_t d) {
    if (node == NULL) return;
    tst_node_show(node->l, d);
    for (size_t i = 0; i < d; i++) printf(" ");
    printf("%c\n", node->c);
    tst_node_show(node->m, d + 1);
    tst_node_show(node->r, d);
}

void tst_show(TernarySearchTries *tst) {
    tst_node_show(tst->root, 0);
}

