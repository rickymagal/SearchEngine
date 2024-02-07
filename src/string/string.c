#include "string.h"

struct string {
    char *c;
    size_t length;
};

String *string_create(const unsigned char *data) {
    String *string = malloc(sizeof(String));
    string->length = strlen(data);
    string->c = malloc(string->length + 1);
    strcpy(string->c, data);

    // parse string to lowercase
    for (size_t i = 0; i < string->length; i++) {
        string->c[i] = tolower(string->c[i]);
    }
    return string;
}

void string_set(String *string, const unsigned char *data) {
    string->length = strlen(data);
    string->c = realloc(string->c, string->length + 1);
    strcpy(string->c, data);
}

void string_show(String *string) {
    printf("%s", string->c);
}

void fprint_string(FILE *fp, String *string) {
    fprintf(fp, "%s", string->c);
}

size_t string_get_length(String *string) {
    return string->length;
}

char string_get_char_at(String *string, size_t i) {
    return string->c[i];
}

int string_compare_from(String *s, String *t, size_t d) {
    int min = string_get_length(s) < string_get_length(t) ? string_get_length(s) : string_get_length(t);
    for (int i = d; i < min; i++) {
        if (string_get_char_at(s, i) < string_get_char_at(t, i))  return -1; 
        if (string_get_char_at(s, i) > string_get_char_at(t, i))  return 1; 
    }
    return string_get_length(s) - string_get_length(t);
}


void string_destroy(String *string) {
    free(string->c);
    free(string);
}

// Função de hash para strings
int hash_fn_string(int table_size, void *key) {
    String *s = (String *) key;
    int hash = 0;
    for (size_t i = 0; i < string_get_length(s); i++) {
        hash += string_get_char_at(s, i);
    }
    return hash % table_size;
}

// Função de comparação de strings
int compare_string(void *key1, void *key2) {
    String *s1 = (String *) key1;
    String *s2 = (String *) key2;
    return string_compare_from(s1, s2, 0);
}

// Função de impressão de strings
void string_print(FILE *f,void *key) {
    String *s = (String *) key;
    fprint_string(f, s);
}

// Função de destruição de strings
void destroy_string(void *key) {
    String *s = (String *) key;
    string_destroy(s);
}

char *get_char_pointer_from_string(String *str) {
    return str->c;
}

// Path: src/string/string.h
