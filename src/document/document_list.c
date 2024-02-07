#include "document_list.h"

DocumentList *document_list_create(int capacity) {
    DocumentList *list = malloc(sizeof(DocumentList));
    list->docs = malloc(capacity * sizeof(Document*));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void document_list_destroy(DocumentList *list) {
    for (int i = 0; i < list->size; i++) {
        document_destroy(list->docs[i]);
    }
    free(list->docs);
    free(list);
}

Document *document_list_get(DocumentList *list, int index) {
    return list->docs[index];
}

void document_list_add(DocumentList *list, Document *doc) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->docs = realloc(list->docs, list->capacity * sizeof(Document*));
    }
    list->docs[list->size++] = doc;
}

int document_list_get_size(DocumentList *list) {
    return list->size;
}

void document_list_sort(DocumentList *list) {
    qsort(list->docs, list->size, sizeof(Document *), document_compare);
}

int document_list_binary_search(DocumentList *list, String *name) {
    int low = 0;
    int high = list->size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        String *mid_name = document_get_name(list->docs[mid]);
        int cmp = string_compare_from(name, mid_name, 0);
        if (cmp < 0) {
            high = mid - 1;
        }
        else if (cmp > 0) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}

int document_list_index_of(DocumentList *list, Document *doc) {
    return document_list_binary_search(list, document_get_name(doc));
}

void document_list_print(DocumentList *list) {
    for (int i = 0; i < list->size; i++) {
        document_print(list->docs[i]);
    }
}
