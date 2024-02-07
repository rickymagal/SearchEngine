#include "document.h"


Document *document_create(String *name) {
    Document *doc = malloc(sizeof(Document));
    doc->name = name;
    doc->rank = 0;
    doc->In = linked_list_construct();
    doc->Out = linked_list_construct();
    return doc;
}

void document_destroy(Document *doc) {
    linked_list_destroy(doc->In);
    linked_list_destroy(doc->Out);
    string_destroy(doc->name);
    free(doc);
}

void document_set_rank(Document *doc, double rank) {
    doc->rank = rank;
}

String *document_get_name(Document *doc) {
    return doc->name;
}

LinkedList *document_get_in(Document *doc) {
    return doc->In;
}

LinkedList *document_get_out(Document *doc) {
    return doc->Out;
}

void document_add_in(Document *doc, Document *in) {
    linked_list_push_front(doc->In, in);
}

void document_add_out(Document *doc, Document *out) {
    linked_list_push_front(doc->Out, out);
}

void document_link_to(Document *doc, Document *to) {
    if(doc == NULL || to == NULL) {
        printf("Document is NULL\n");
        return;
    }
    document_add_in(to, doc);
    document_add_out(doc, to);
}

int document_get_in_size(Document *doc) {
    return linked_list_get_size(doc->In);
}

int document_get_out_size(Document *doc) {
    return linked_list_get_size(doc->Out);
}

int document_compare(const void *a, const void *b) {
    Document **doc_a = (Document **)a;
    Document **doc_b = (Document **)b;
    return string_compare_from(document_get_name(*doc_a), document_get_name(*doc_b), 0);
}

int document_compare_with_rank(const void *a, const void *b) {
    Document *doc_a = *(Document **)a;
    Document *doc_b = *(Document **)b;

    if(doc_a->rank > doc_b->rank) {
        return -1;
    } else if(doc_a->rank < doc_b->rank) {
        return 1;
    } else {
        return string_compare_from(document_get_name(doc_a), document_get_name(doc_b), 0);
    }
}

size_t document_sizeof() {
    return sizeof(Document);
}

void document_print_aux(void *doc) {
    string_show(document_get_name((Document*) doc));
}

void document_print(Document *doc) {
    string_show(doc->name);
    printf(" (%.16lf)", doc->rank);
}
