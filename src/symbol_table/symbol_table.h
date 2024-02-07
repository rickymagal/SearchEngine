#ifndef _SYMBOL_TABLE__
#define _SYMBOL_TABLE__

#include "../ternary_search_tries/ternary_search_tries.h"
#include "../types.h"

typedef struct symbol_table SymbolTable;


/**
 * @brief Cria uma symbol table
 * 
 * @param cmp Ponteiro para funçäo de comparação entre nodes
 * @param key_destroy Ponteiro para funçäo de destruição de uma key
 * @param val_destroy Ponteiro para funçäo de destruição de um value
 * @return Nova symbol table 
 */
SymbolTable *symbol_table_init(CmpFunction cmp, DestroyFunction key_destroy, DestroyFunction val_destroy);


/**
 * @brief Libera a memória alocada pela symbol table 
 * 
 * @param st Symbol table
 */
void symbol_table_destroy(SymbolTable *st);

/**
 * @brief Adiciona um novo node ou muda o valor de um node já existente na symbol table
 * 
 * @param st Symbol table
 * @param key Chave a ser usada
 * @param val Valor a ser usado
 */
void symbol_table_put(SymbolTable *st, Key key, Value val);

/**
 * @brief Retorna o valor que faz par com a chave determinada
 * 
 * @param st Symbol table
 * @param key Chave determinada
 * @return Valor 
 */
Value symbol_table_get(SymbolTable *st, Key key);

/**
 * @brief Verifica se o node correspondente à chave desejada existe
 * 
 * @param st Symbol table
 * @param key Chave a ser procurada
 * @return True se o node existe, caso contrário, false
 */
bool symbol_table_exists(SymbolTable *st, Key key);

/**
 * @brief Verifica se o valor correspondente à chave desejada existe
 * 
 * @param st Symbol table
 * @param key Chave a ser procurada
 * @return True se o valor existe, caso contrário, false 
 */
bool symbol_table_contains(SymbolTable *st, Key key);

/**
 * @brief Verifica se a symbol table não possui nenhum node
 * 
 * @param st Symbol table
 * @return True se estiver vazia, caso contrário, false  
 */
bool symbol_table_empty(SymbolTable *st);

/**
 * @brief Imprime os valores armazenados na symbol table a partir de uma analise inorder 
 * 
 * @param st Symbol table
 * @param key_print Ponteiro para funcao de impressão das chaves
 * @param val_print Ponteiro para funcao de impressão dos valores
 */
void symbol_table_inorder_print(SymbolTable* st, void (*key_print)(void*), void (*val_print)(void*));

#endif