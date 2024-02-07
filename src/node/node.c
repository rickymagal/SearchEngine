#include "node.h"

struct node {
    data_type data;
    struct node *next;
};

// Cria um novo nó
Node *node_contruct(data_type data, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = next;
    return node;
    
}

// Destroi um nó
void node_destroy(Node *node) {
    free(node);
}

bool node_is_null(Node *node) {
    return node == NULL;
}

data_type node_get_data(Node *node) {
    return node->data;
}

Node* node_get_next(Node *node) {
    return node->next;
}

void node_set_data(Node *node, data_type data) {
    node->data = data;
}

void node_set_next(Node *node, Node *next) {
    node->next = next;
}
