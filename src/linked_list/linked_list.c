#include "linked_list.h"

struct linked_list {
    Node *head;
    size_t size;
};


// Cria uma nova lista
LinkedList *linked_list_construct() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

Node *linked_list_get_head(LinkedList *list) {
    return list->head;
}

void linked_list_set_head(LinkedList *list, Node *head) {
    list->head = head;
}

// Destroi uma lista
void linked_list_destroy(LinkedList *list) {
    Node *node = list->head;
    while (!node_is_null(node)) {
        Node *next = node_get_next(node);
        node_destroy(node);
        node = next;
    }
    free(list);
}

// Verifica se a lista está vazia
bool linked_list_is_empty(LinkedList *list) {
    return list->size == 0;
}

// Pega o tamanho da lista
size_t linked_list_get_size(LinkedList *list) {
    return list->size;
}

// Pega o primeiro elemento da lista
void* linked_list_get_first(LinkedList *list) {
    return node_get_data(list->head);
}

// Pega o último elemento da lista
void* linked_list_get_last(LinkedList *list) {
    Node *node = list->head;
    while (!node_is_null(node_get_next(node))) {
        node = node_get_next(node);
    }
    return node_get_data(node);
}

// Pega o elemento de uma posição da lista
void* linked_list_get(LinkedList *list, size_t index) {
    Node *node = list->head;
    for (size_t i = 0; i < index; i++) {
        node = node_get_next(node);
    }
    return node_get_data(node);
}

// Adiciona um elemento no início da lista
void linked_list_push_front(LinkedList *list, void *data) {
    Node *node = node_contruct(data, list->head);
    list->head = node;
    list->size++;
}

// Adiciona um elemento no final da lista
void linked_list_add_last(LinkedList *list, void *data) {
    Node *node = node_contruct(data, NULL);
    if (linked_list_is_empty(list)) {
        list->head = node;
    } else {
        Node *last = list->head;
        while (!node_is_null(node_get_next(last))) {
            last = node_get_next(last);
        }
        node_set_next(last, node);
    }
    list->size++;
}

// Adiciona um elemento em uma posição da lista
void linked_list_add(LinkedList *list, void *data, size_t index) {
    if (index == 0) {
        linked_list_push_front(list, data);
        return;
    }
    if (index == list->size) {
        linked_list_add_last(list, data);
        return;
    }
    Node *node = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        node = node_get_next(node);
    }
    Node *next = node_get_next(node);
    Node *new_node = node_contruct(data, next);
    node_set_next(node, new_node);
    list->size++;
}

// Remove o primeiro elemento da lista
void linked_list_remove_first(LinkedList *list) {
    Node *node = list->head;
    list->head = node_get_next(node);
    node_destroy(node);
    list->size--;
}

// Remove o último elemento da lista
void linked_list_remove_last(LinkedList *list) {
    Node *node = list->head;
    while (!node_is_null(node_get_next(node_get_next(node)))) {
        node = node_get_next(node);
    }
    node_destroy(node_get_next(node));
    node_set_next(node, NULL);
    list->size--;
}

// Remove um elemento de uma posição da lista
void linked_list_remove(LinkedList *list, size_t index) {
    if (index == 0) {
        linked_list_remove_first(list);
        return;
    }
    if (index == list->size - 1) {
        linked_list_remove_last(list);
        return;
    }
    Node *node = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        node = node_get_next(node);
    }
    Node *next = node_get_next(node_get_next(node));
    node_destroy(node_get_next(node));
    node_set_next(node, next);
    list->size--;
}

// Remove todos os elementos da lista
void linked_list_clear(LinkedList *list) {
    Node *node = list->head;
    while (!node_is_null(node)) {
        Node *next = node_get_next(node);
        node_destroy(node);
        node = next;
    }
    list->head = NULL;
    list->size = 0;
}

// Verifica se a lista contém um elemento
bool linked_list_contains(LinkedList *list, void *data) {
    Node *node = list->head;
    while (!node_is_null(node)) {
        if (node_get_data(node) == data) {
            return true;
        }
        node = node_get_next(node);
    }
    return false;
}

// Pega a posição de um elemento na lista
size_t linked_list_index_of(LinkedList *list, void *data) {
    Node *node = list->head;
    size_t index = 0;
    while (!node_is_null(node)) {
        if (node_get_data(node) == data) {
            return index;
        }
        node = node_get_next(node);
        index++;
    }
    return -1;
}

// Pega a última posição de um elemento na lista
size_t linked_list_last_index_of(LinkedList *list, void *data) {
    Node *node = list->head;
    size_t index = 0;
    size_t last_index = -1;
    while (!node_is_null(node)) {
        if (node_get_data(node) == data) {
            last_index = index;
        }
        node = node_get_next(node);
        index++;
    }
    return last_index;
}

// Pega um sublista de uma lista
LinkedList* linked_list_sub_list(LinkedList *list, size_t from, size_t to) {
    LinkedList *sub_list = linked_list_construct();
    Node *node = list->head;
    for (size_t i = 0; i < from; i++) {
        node = node_get_next(node);
    }
    for (size_t i = from; i < to; i++) {
        linked_list_add_last(sub_list, node_get_data(node));
        node = node_get_next(node);
    }
    return sub_list;
}

// Copia uma lista
LinkedList* linked_list_copy(LinkedList *list) {
    LinkedList *copy = linked_list_construct();
    Node *node = list->head;
    while (!node_is_null(node)) {
        linked_list_add_last(copy, node_get_data(node));
        node = node_get_next(node);
    }
    return copy;
}

// Inverte uma lista
void linked_list_reverse(LinkedList *list) {
    Node *node = list->head;
    Node *prev = NULL;
    while (!node_is_null(node)) {
        Node *next = node_get_next(node);
        node_set_next(node, prev);
        prev = node;
        node = next;
    }
    list->head = prev;
}

// Imprime uma lista
void linked_list_print(LinkedList *list, void (*print)(void *)) {
    printf("[");
    Node *node = list->head;
    while (!node_is_null(node)) {
        print(node_get_data(node));
        if (!node_is_null(node_get_next(node))) {
            printf(", ");
        }
        node = node_get_next(node);
    }
    printf("]");
}

// Itera sobre os elementos de uma lista
void linked_list_for_each(LinkedList *list, void (*callback)(void *)) {
    Node *node = list->head;
    while (!node_is_null(node)) {
        callback(node_get_data(node));
        node = node_get_next(node);
    }
}

// Linked list to vector
Vector* linked_list_to_vector(LinkedList *list) {
    Vector *vector = vector_new(list->size);
    Node *node = list->head;
    while (!node_is_null(node)) {
        vector_push_back(vector, node_get_data(node));
        node = node_get_next(node);
    }
    return vector;
}

// Insere um elemento ordenado na lista (recursive)
Node *sorted_insert(Node *head, Node *new_node, int (*compare)(const void *, const void *)) {
    if (node_is_null(head)) {
        return new_node;
    }
    if (compare(node_get_data(head), node_get_data(new_node)) > 0) {
        node_set_next(new_node, head);
        return new_node;
    }
    node_set_next(head, sorted_insert(node_get_next(head), new_node, compare));
    return head;
}

// Insertion sort
void linked_list_sort(LinkedList *list, int (*compare)(const void *, const void *)) {
    Node *sorted = NULL;
    Node *current = list->head;
    while (!node_is_null(current)) {
        Node *next = node_get_next(current);
        sorted = sorted_insert(sorted, current, compare);
        current = next;
    }
    list->head = sorted;
}
