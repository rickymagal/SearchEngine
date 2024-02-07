#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../types.h"

typedef struct vector {
    size_t size;
    size_t capacity;
    data_type *data;
} Vector;

/// @brief Cria um novo vetor
/// @param capacity 
/// @return Novo vetor
Vector *vector_new(size_t capacity);

/// @brief Libera a memória alocada pelo vetor
/// @param vector Vetor
/// @param destroy Função de destruição dos dados
void vector_destroy(Vector *vector, void (*destroy)(void *));

/// @brief Adiciona um elemento no final do vetor
/// @param vector Vetor
/// @param data Dado
void vector_push_back(Vector *vector, data_type data);

/// @brief Remove o último elemento do vetor
/// @param vector Vetor
/// @return Dado removido
data_type vector_pop_back(Vector *vector);

/// @brief Adiciona um elemento na posição especificada
/// @param vector Vetor
/// @param index Posição
/// @param data Dado
void vector_insert(Vector *vector, size_t index, data_type data);

/// @brief 
/// @param vector 
/// @param index 
/// @param data 
/// @return 
data_type vector_insert_at(Vector *vector, size_t index, data_type data);

/// @brief Remove um elemento na posição especificada
/// @param vector Vetor
/// @param index Posição
data_type vector_remove(Vector *vector, size_t index);

/// @brief Remove um elemento na posição especificada
/// @param vector Vetor
/// @param index Posição
/// @param data Dado
data_type vector_at(Vector *vector, size_t index);

/// @brief Pega o primeiro elemento do vetor
/// @param vector Vetor
/// @return Dado
data_type vector_get_front(Vector *vector);

/// @brief Pega o último elemento do vetor
/// @param vector Vetor
/// @return Dado
data_type vector_get_back(Vector *vector);

/// @brief Pega o tamanho do vetor
/// @param vector Vetor
/// @return Tamanho
size_t vector_get_size(Vector *vector);

/// @brief Pega a capacidade do vetor
/// @param vector Vetor
/// @return Capacidade
size_t vector_get_capacity(Vector *vector);

/// @brief Verifica se o vetor está vazio
/// @param vector Vetor
/// @return Verdadeiro se estiver vazio, falso caso contrário
bool vector_is_empty(Vector *vector);

/// @brief Imprime o vetor
/// @param vector Vetor
/// @param print Função de impressão
void vector_print(Vector *vector, void (*print)(void *));

/// @brief Copia o vetor
/// @param vector Vetor
/// @return Novo vetor
Vector *vector_copy(Vector *vector);

/// @brief Inverte o vetor
/// @param vector Vetor
void vector_reverse(Vector *vector);

/// @brief Ordena o vetor
/// @param vector Vetor
/// @param compare Função de comparação
void vector_sort(Vector *vector, int (*compare)(const void *, const void *));

/// @brief Mescla dois vetores
/// @param vector Vetor
/// @param other Outro vetor
/// @return Novo vetor
Vector *vector_merge(Vector *vector, Vector *other);

bool vector_contains_null(Vector *vector);

data_type vector_get_max(Vector *vector, int (*cmp)(void *, void *));

#endif // VECTOR_H