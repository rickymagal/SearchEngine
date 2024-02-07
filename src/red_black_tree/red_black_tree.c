#include "red_black_tree.h"

struct red_black_tree {
    RedBlackTreeNode *root;
    CmpFunction cmp;
    DestroyFunction key_destroy;
    DestroyFunction val_destroy;
};

struct red_black_tree_node {
    Key key;
    Value val;
    RedBlackTreeNode *l, *r;
    bool color;
};

bool is_red(RedBlackTreeNode *x) {
    if (x == NULL)  return BLACK;
    else            return x->color;
}

RedBlackTreeNode *red_black_tree_node_create(Key key, Value val) {
    RedBlackTreeNode *node = (RedBlackTreeNode*) malloc(sizeof(RedBlackTreeNode));
    node->key = key;
    node->val = val;
    node->color = RED;
    node->l = NULL;
    node->r = NULL;

    return node;
}

void red_black_tree_node_destroy(RedBlackTreeNode *n, DestroyFunction key_destroy, DestroyFunction val_destroy) {
    if (n == NULL)  return;
    red_black_tree_node_destroy(n->l, key_destroy, val_destroy);
    red_black_tree_node_destroy(n->r, key_destroy, val_destroy);
    key_destroy(n->key);
    val_destroy(n->val);
    free(n);
}

RedBlackTreeNode *rotate_left(RedBlackTreeNode *t) {
    RedBlackTreeNode *x = t->r;
    t->r = x->l;
    x->l = t;
    x->color = x->l->color;
    x->l->color = RED;

    return x;
}

RedBlackTreeNode *rotate_right(RedBlackTreeNode *t) {
    RedBlackTreeNode *x = t->l;
    t->l = x->r;
    x->r = t;
    x->color = x->r->color;
    x->r->color = RED;

    return x;
}

void color_flip(RedBlackTreeNode *t) {
    t->color = RED;
    t->l->color = BLACK;
    t->r->color = BLACK;
}


RedBlackTree *red_black_tree_create(CmpFunction cmp, DestroyFunction key_destroy, DestroyFunction val_destroy) {
    RedBlackTree *t = (RedBlackTree*) malloc(sizeof(RedBlackTree));
    t->root = NULL;
    t->cmp = cmp;
    t->key_destroy = key_destroy;
    t->val_destroy = val_destroy;

    return t;
}

void red_black_tree_destroy(RedBlackTree *t) {
    red_black_tree_node_destroy(t->root, t->key_destroy, t->val_destroy);
    free(t);
}

Value red_black_tree_search(RedBlackTree *t, Key key) {
    RedBlackTreeNode *x = t->root;
    while (x != NULL) {
        int cmp = t->cmp(key, x->key);
        if      (cmp < 0)   x = x->l;
        else if (cmp > 0)   x = x->r;
        else                return x->val;
    }

    return NULL_Value;
}

RedBlackTreeNode *red_black_tree_insert_aux(RedBlackTree *tree, RedBlackTreeNode *t, Key key, Value val) {
    if (t == NULL)  return red_black_tree_node_create(key, val);

    int cmp = tree->cmp(key, t->key);  
    if      (cmp < 0)   t->l = red_black_tree_insert_aux(tree, t->l, key, val);
    else if (cmp > 0)   t->r = red_black_tree_insert_aux(tree, t->r, key, val);
    else {
        Value old_val = t->val;
        t->val = val; 
        tree->val_destroy(old_val);
        tree->key_destroy(key);
    }

    if (is_red(t->r) && !is_red(t->l))      t = rotate_left(t);
    if (is_red(t->l) && is_red(t->l->l))    t = rotate_right(t);
    if (is_red(t->l) && is_red(t->r))       color_flip(t);

    return t;
}

void *red_black_tree_insert(RedBlackTree *t, Key key, Value val) {
    t->root = red_black_tree_insert_aux(t, t->root, key, val);
}

void aux_inorder_print(RedBlackTreeNode *t, void (*key_print)(void*), void (*val_print)(void*)) {
    if(t == NULL) return;
    aux_inorder_print(t->l, key_print, val_print);
    key_print(t->key);
    printf(" -> ");
    val_print(t->val);
    printf("\n");
    aux_inorder_print(t->r, key_print, val_print);
}

void red_black_tree_inorder_print(RedBlackTree *t, void (*key_print)(void*), void (*val_print)(void*)) {
    aux_inorder_print(t->root, key_print, val_print);
}

bool red_black_tree_empty(RedBlackTree *t) {
    return t->root == NULL;
}