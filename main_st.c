#include "src/symbol_table/symbol_table.h"
#include "src/string/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int N = 1e7; 
    
    SymbolTable *st = symbol_table_init(NULL, NULL, (void (*)(void *))free);

    String *temp = string_create(""); // string vazia, para ser usada como chave

    // Armazena as N strings aleatórias em um vetor de strings, para pesquisar posteriormente
    char **strs = malloc(sizeof(char *) * N);

    int count = 0;
    for (int i = 0; i < N; i++) {
        int len = rand() % 10 + 1;
        char *str = malloc(sizeof(char) * (len + 1));
        for (int j = 0; j < len; j++) {
            str[j] = rand() % 26 + 'a';
        }
        str[len] = '\0';

        // str é uma string aleatória de tamanho len, tambem aleatório de 1 a 10
        string_set(temp, str);

        // Verifica se a chave já existe na tabela
        if (symbol_table_contains(st, temp)) {
            free(str);
            continue;
        }

        // Armazena a string aleatória no vetor de strings
        strs[count] = malloc(sizeof(char) * (len + 1));

        strcpy(strs[count++], str);

        // string_set faz uma cópia de str, então podemos liberar a memória
        free(str);

        // Aloca um valor a ser armazenado na tabela
        int *val = malloc(sizeof(int));

        // Armazena o valor i na tabela
        *val = i;

        // Insere na tabela
        symbol_table_put(st, temp, val);
    }

    // symbol_table_inorder_print(st, NULL, NULL);


    // Pesquisa as count strings aleatórias no vetor de strings
    for (int i = 0; i < count; i++) {
        string_set(temp, strs[i]);
        if (!symbol_table_contains(st, temp)) {
            printf("Erro: %s não está na tabela\n", strs[i]);
            exit(1);
        }
    }

    string_destroy(temp);
    // Libera a memória alocada para as strings aleatórias
    for (int i = 0; i < count; i++) {
        free(strs[i]);
    }
    free(strs);
    symbol_table_destroy(st);
    return 0;
}
