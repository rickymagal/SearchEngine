#ifndef _REDBLACK_TREE_
#define _REDBLACK_TREE_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../types.h"

#define RED true
#define BLACK false
#define NULL_Value NULL
#define NULL_Key NULL



typedef struct red_black_tree RedBlackTree;
typedef struct red_black_tree_node RedBlackTreeNode;

/// @brief Cria uma nova árvore rubro-negra
/// @param cmp Função de comparação entre chaves
/// @param key_destroy Função de destruição de chaves
/// @param val_destroy Função de destruição de valores
/// @return Ponteiro para a árvore rubro-negra criada
RedBlackTree *red_black_tree_create(CmpFunction cmp, DestroyFunction key_destroy, DestroyFunction val_destroy);

/// @brief Destrói uma árvore rubro-negra
/// @param t Árvore rubro-negra a ser destruída
void red_black_tree_destroy(RedBlackTree *t);

/// @brief Busca na árvore rubro-negra
/// @param n Árvore rubro-negra
/// @param key Chave a ser buscada
/// @return Valor associado à chave, ou um valor nulo se a chave não for encontrada
Value red_black_tree_search(RedBlackTree *n, Key key);

/// @brief Insere um novo nó na árvore rubro-negra
/// @param t Árvore rubro-negra
/// @param key Chave do nó a ser inserido
/// @param val Valor associado ao nó a ser inserido
/// @return Ponteiro para o nó recém-inserido
void *red_black_tree_insert(RedBlackTree *t, Key key, Value val);

/// @brief Imprime a árvore rubro-negra em ordem
/// @param t Árvore rubro-negra a ser impressa
/// @param key_print Função de impressão para chaves
/// @param val_print Função de impressão para valores
void red_black_tree_inorder_print(RedBlackTree *t, void (*key_print)(void*), void (*val_print)(void*));

/// @brief Verifica se a árvore rubro-negra está vazia
/// @param t Árvore rubro-negra
/// @return Verdadeiro se a árvore rubro-negra estiver vazia, falso caso contrário
bool red_black_tree_empty(RedBlackTree *t);

#endif // _REDBLACK_TREE_