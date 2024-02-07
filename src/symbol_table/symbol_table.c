#include "symbol_table.h"


struct symbol_table {
    TernarySearchTries *tst;
};


SymbolTable *symbol_table_init(CmpFunction cmp, DestroyFunction key_destroy, DestroyFunction val_destroy) {
    SymbolTable *st = (SymbolTable*) malloc(sizeof(SymbolTable));
    st->tst = tst_create(val_destroy);

    return st;
}

void symbol_table_destroy(SymbolTable *st) {
    tst_destroy(st->tst);
    free(st);
}

void symbol_table_put(SymbolTable *st, Key key, Value val) {
    tst_insert(st->tst, key, val);
}

Value symbol_table_get(SymbolTable *st, Key key) {
    return tst_get(st->tst, key);
}

bool symbol_table_exists(SymbolTable *st, Key key) {
    return tst_exists(st->tst, key);
}

bool symbol_table_contains(SymbolTable *st, Key key) {
    return tst_contains(st->tst, key);
}

// RED FLAG: 
void symbol_table_delete(SymbolTable *st, Key key) {
    printf("TODO: Implementar symbol_table_delete\n");
    exit(1);
}

bool symbol_table_empty(SymbolTable *st) {
    return tst_is_empty(st->tst);
}

void symbol_table_inorder_print(SymbolTable*st, void (*key_print)(void*), void (*val_print)(void*)) {
    tst_show(st->tst);
}
