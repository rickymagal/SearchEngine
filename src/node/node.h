#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>
#include <stdbool.h>
#include "../types.h"

typedef struct node Node;


/// @brief Cria um novo nó
/// @param data Dado
/// @param next Próximo nó
/// @return Novo nó
Node *node_contruct(data_type data, Node *next);

/// @brief Libera a memória alocada pelo nó
/// @param node Nó
void node_destroy(Node *node);

/// @brief Verifica se o nó é nulo
/// @param node Nó
/// @return Verdadeiro se o nó for nulo, falso caso contrário
bool node_is_null(Node *node);

/// @brief Pega o conteudo do nó
/// @param node Nó
/// @return Conteudo do nó
data_type node_get_data(Node *node);

/// @brief Pega o próximo nó
/// @param node Nó
/// @return Próximo nó
Node* node_get_next(Node *node);

/// @brief Define o conteudo do nó
/// @param node Nó
/// @param data Conteudo
void node_set_data(Node *node, data_type data);

/// @brief Define o próximo nó
/// @param node Nó
/// @param next Próximo nó
void node_set_next(Node *node, Node *next);

#endif // _NODE_H_