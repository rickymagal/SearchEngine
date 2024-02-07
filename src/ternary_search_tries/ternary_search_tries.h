#ifndef TERNARY_SEARCH_TRIES_H
#define TERNARY_SEARCH_TRIES_H

#include "../types.h"
#include "../string/string.h"

typedef struct ternary_search_tries TernarySearchTries;

/// @brief Create a new Ternary Search Tries
/// @return A pointer to the new Ternary Search Tries
TernarySearchTries *tst_create();

/// @brief Destroy a Ternary Search Tries
/// @param tst A pointer to the Ternary Search Tries to destroy
void tst_destroy(TernarySearchTries *tst);

/// @brief Insert a new key-value pair into the Ternary Search Tries
/// @param tst A pointer to the Ternary Search Tries
/// @param key A pointer to the key
/// @param val The value to insert
void tst_insert(TernarySearchTries *tst, String *key, Value val);

/// @brief Get the value associated with the key
/// @param tst A pointer to the Ternary Search Tries
/// @param key A pointer to the key
Value tst_get(TernarySearchTries *tst, String *key);

/// @brief Verify if the key exists in the Ternary Search Tries
/// @param tst A pointer to the Ternary Search Tries
/// @param key A pointer to the key
/// @return True if the key exists, false otherwise
bool tst_exists(TernarySearchTries *tst, String *key);

/// @brief Verify if the key exists in the Ternary Search Tries
/// @param tst A pointer to the Ternary Search Tries
/// @param key A pointer to the key
bool tst_contains(TernarySearchTries *tst, String *key);

/// @brief Verify if the Ternary Search Tries is empty
/// @param tst A pointer to the Ternary Search Tries
/// @return True if the Ternary Search Tries is empty, false otherwise
bool tst_is_empty(TernarySearchTries *tst);

void tst_show(TernarySearchTries *tst);

#endif // TERNARY_SEARCH_TRIES_H