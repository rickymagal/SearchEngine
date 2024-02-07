#include "vector.h"

Vector *vector_new(size_t capacity) {
    Vector *vector = (Vector *) malloc(sizeof(Vector));
    vector->capacity = capacity;
    vector->size = 0;
    vector->data = (data_type *) malloc(sizeof(data_type) * capacity);
    return vector;
}

void vector_destroy(Vector *vector, void (*destroy)(void *)) {
    if(destroy != NULL) {
        for (size_t i = 0; i < vector->size; i++) {
            destroy(vector->data[i]);
        }
    }
    free(vector->data);
    free(vector);
}

void vector_push_back(Vector *vector, data_type data) {
    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        vector->data = (data_type *) realloc(vector->data, sizeof(data_type) * vector->capacity);
    }
    vector->data[vector->size++] = data;
}

data_type vector_pop_back(Vector *vector) {
    if (vector->size > 0) {
        vector->size--;
    }

    if (vector->size <= vector->capacity / 4) {
        vector->capacity /= 2;
        vector->data = (data_type *) realloc(vector->data, sizeof(data_type) * vector->capacity);
    }

    return vector->data[vector->size];
}

void vector_insert(Vector *vector, size_t index, data_type data) {
    if (index > vector->size) {
        return;
    }

    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        vector->data = (data_type *) realloc(vector->data, sizeof(data_type) * vector->capacity);
    }

    for (size_t i = vector->size; i > index; i--) {
        vector->data[i] = vector->data[i - 1];
    }

    vector->data[index] = data;
    vector->size++;

}

data_type vector_insert_at(Vector *vector, size_t index, data_type data) {
    data_type old = vector->data[index];
    vector->data[index] = data;
    return old;
}

data_type vector_remove(Vector *vector, size_t index) {
    if (index >= vector->size) {
        return NULL;
    }

    data_type data = vector->data[index];

    for (size_t i = index; i < vector->size - 1; i++) {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;

    if (vector->size <= vector->capacity / 4) {
        vector->capacity /= 2;
        vector->data = (data_type *) realloc(vector->data, sizeof(data_type) * vector->capacity);
    }

    return data;

}

data_type vector_at(Vector *vector, size_t index) {
    if (index >= vector->size) {
        return NULL;
    }
    return vector->data[index];
}

data_type vector_get_front(Vector *vector) {
    if (vector->size == 0) {
        return NULL;
    }
    return vector->data[0];

}

data_type vector_get_back(Vector *vector) {
    if (vector->size == 0) {
        return NULL;
    }
    return vector->data[vector->size - 1];
}

size_t vector_get_size(Vector *vector) {
    return vector->size;
}

size_t vector_get_capacity(Vector *vector) {
    return vector->capacity;
}

bool vector_is_empty(Vector *vector) {
    return vector->size == 0;
}

void vector_print(Vector *vector, void (*print)(void *)) {
    printf("[");
    for (size_t i = 0; i < vector->size; i++) {
        print(vector->data[i]);
        if (i != vector->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

Vector *vector_copy(Vector *vector) {
    Vector *copy = vector_new(vector->capacity);
    copy->size = vector->size;
    for (size_t i = 0; i < vector->size; i++) {
        copy->data[i] = vector->data[i];
    }
    return copy;
}

void vector_reverse(Vector *vector) {
    for (size_t i = 0; i < vector->size / 2; i++) {
        data_type temp = vector->data[i];
        vector->data[i] = vector->data[vector->size - i - 1];
        vector->data[vector->size - i - 1] = temp;
    }
}

void vector_sort(Vector *vector, int (*compare)(const void *, const void *)) {
    qsort(vector->data, vector->size, sizeof(data_type), compare);    
}

Vector *vector_merge(Vector *vector, Vector *other) {
    Vector *merged = vector_new(vector->size + other->size);
    for (size_t i = 0; i < vector->size; i++) {
        vector_push_back(merged, vector->data[i]);
    }
    for (size_t i = 0; i < other->size; i++) {
        vector_push_back(merged, other->data[i]);
    }
    return merged;
}


bool vector_contains_null(Vector *vector) {
    for(int i = 0; i < vector_get_size(vector); i++) {
        if(vector_at(vector, i) == NULL) 
            return true;
    }
    return false;
}

data_type vector_get_max(Vector *vector, int (*cmp)(void *, void *)) {
    data_type max = vector_at(vector, 0);

    for(int i = 1; i < vector_get_size(vector); i++) {
        data_type current = vector_at(vector, i);
        if(cmp(current, max) > 0) {
            max = current;
        }
    }

    return max;
}