#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct string String;

/// @brief Create a new String object
/// @param data The string data
/// @return A new String object
String *string_create(const unsigned char *data);

/// @brief Set the string data
/// @param string
/// @param data
void string_set(String *string, const unsigned char *data);

/// @brief Show the string
/// @param string 
void string_show(String *string);

/// @brief Print the string
/// @param fp The file to print to
/// @param string 
void fprint_string(FILE *fp, String *string);

/// @brief Get the length of the string
/// @param string
/// @return The length of the string
size_t string_get_length(String *string);

/// @brief Get the char at the index i
/// @param string
/// @param i
/// @return The char at the index i
char string_get_char_at(String *string, size_t i);

/// @brief Compare two strings from the index i
/// @param str_a
/// @param str_b
/// @param i
/// @return 0 if the strings are equal, -1 if str_a < str_b, 1 if str_a > str_b
int string_compare_from(String *str_a, String *str_b, size_t i);

/// @brief Free the string
/// @param string
void string_destroy(String *string);

/// @brief Calculate the hash of the string
/// @param table_size Size of the vector
/// @param key The string
/// @return The hash of the string
int hash_fn_string(int table_size, void *key);

/// @brief Compare two strings
/// @param key1 String 1
/// @param key2 String 2
/// @return 0 if the strings are equal, -1 if str_a < str_b, 1 if str_a > str_b
int compare_string(void *key1, void *key2);

/// @brief Print the string
/// @param f The file to print to
/// @param key The string
void string_print(FILE *f,void *key);

/// @brief Destroy the string
/// @param key The string
void destroy_string(void *key);

char *get_char_pointer_from_string(String *str);

#endif // STRING_H
