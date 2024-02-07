#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../node/node.h"
#include "../vector/vector.h"

typedef struct linked_list LinkedList;


/**
 * @brief Cria uma linked list
 * 
 * @return Nova linked list
 */
LinkedList *linked_list_construct();

/**
 * @brief Retorna o node correspondente à head da linked list
 * 
 * @param list Linked list 
 * @return Head
 */
Node *linked_list_get_head(LinkedList *list);

/**
 * @brief Atualiza a head com um novo node
 * 
 * @param list Linked list
 * @param head Novo node correspondente à head
 */
void linked_list_set_head(LinkedList *list, Node *head);

/**
 * @brief Libera a memória alocada pela linked list
 * 
 * @param list Linked list
 */
void linked_list_destroy(LinkedList *list);

/**
 * @brief Verifica se a linked list não possui nenhum node
 * 
 * @param list Linked list
 * @return True se estiver vazia, caso contrário, false   
 */
bool linked_list_is_empty(LinkedList *list);

/**
 * @brief Retorna a quantidade de nodes pertencentes à linked list (tamanho)
 * 
 * @param list Linked list
 * @return Tamanho 
 */
size_t linked_list_get_size(LinkedList *list);

/**
 * @brief Retorna o conteúdo do primeiro node da lista
 * 
 * @param list Linked list
 * @return Data 
 */
void* linked_list_get_first(LinkedList *list);

/**
 * @brief Retorna o conteúdo do último node da lista
 * 
 * @param list Linked list
 * @return Data 
 */
void* linked_list_get_last(LinkedList *list);

/**
 * @brief Retorna o conteúdo do node de determinado índice da lista
 * 
 * @param list Linked list
 * @param index Índice
 * @return Data
 */
void* linked_list_get(LinkedList *list, size_t index);

/**
 * @brief Adiciona um novo node no início da linked list
 * 
 * @param list Linked list
 * @param data Data do node
 */
void linked_list_push_front(LinkedList *list, void *data);

/**
 * @brief Adiciona um novo node no final da linked list
 * 
 * @param list Linked list
 * @param data Data do novo node
 */
void linked_list_add_last(LinkedList *list, void *data);

/**
 * @brief Adiciona um novo node em um determinado índice da lista
 * 
 * @param list Linked list
 * @param data Data do node
 * @param index Índice 
 */
void linked_list_add(LinkedList *list, void *data, size_t index);

/**
 * @brief Remove o primeiro node da lista
 * 
 * @param list Linked list
 */
void linked_list_remove_first(LinkedList *list);

/**
 * @brief Remove o último node da lista
 * 
 * @param list Linked list
 */
void linked_list_remove_last(LinkedList *list);

/**
 * @brief Remove o node de um determinado índice da lista
 * 
 * @param list 
 * @param index 
 */
void linked_list_remove(LinkedList *list, size_t index);

/**
 * @brief Remove todos os elementos da lista
 * 
 * @param list Linked list
 */
void linked_list_clear(LinkedList *list);

/**
 * @brief Verifica se a lista contém um elemento
 * 
 * @param list Linked list
 * @param data Conteúdo procurado
 * @return True se o node existir, caso contrário, false   
 */
bool linked_list_contains(LinkedList *list, void *data);

/**
 * @brief Retorna o índice de um elemento da lista
 * 
 * @param list Linked list
 * @param data Conteúdo procurado
 * @return Índice 
 */
size_t linked_list_index_of(LinkedList *list, void *data);

/**
 * @brief Retorna a última posição de um elemento na lista
 * 
 * @param list Linked list
 * @param data Conteúdo analisado
 * @return Índice 
 */
size_t linked_list_last_index_of(LinkedList *list, void *data);

/**
 * @brief Retorna uma sublista de uma lista
 * 
 * @param list Linked list
 * @param from Índice inicial
 * @param to Índice final
 * @return Sublista
 */
LinkedList* linked_list_sub_list(LinkedList *list, size_t from, size_t to);

/**
 * @brief Copia uma lista
 * 
 * @param list Linked list
 * @return Cópia 
 */
LinkedList* linked_list_copy(LinkedList *list);

/**
 * @brief Inverte uma lista
 * 
 * @param list Linked list
 */
void linked_list_reverse(LinkedList *list);

/**
 * @brief Imprime os elementos de uma lista
 * 
 * @param list Linked list
 * @param print Ponteiro para função de impressão
 */
void linked_list_print(LinkedList *list, void (*print)(void *));

/**
 * @brief Itera sobre os elementos de uma lista
 * 
 * @param list Linked list
 * @param callback Ponteiro de funcão para um callback  
 */
void linked_list_for_each(LinkedList *list, void (*callback)(void *));

/**
 * @brief Cria um vector com os elementos de uma linked list
 * 
 * @param list Linked list
 * @return Novo vector 
 */
Vector* linked_list_to_vector(LinkedList *list);

/**
 * @brief Realiza o insertion sort sobre uma lista
 * 
 * @param list Linked list
 * @param compare Ponteiro de função para a função de comparação
 */
void linked_list_sort(LinkedList *list, int (*compare)(const void *, const void *));


#endif // LINKED_LIST_H