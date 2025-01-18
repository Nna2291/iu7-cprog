#ifndef BST_TREE_H
#define BST_TREE_H

#include "associative_array.h"

typedef struct bst_node
{
    char *key;
    int value;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t;

// Вставка нового узла в дерево
bst_node_t *bst_insert_node(bst_node_t *root, const char *key, int value, assoc_array_error_t *err);

// Поиск по дереву
bst_node_t *bst_find_node(bst_node_t *root, const char *key);

// Удаление узла
bst_node_t *bst_remove_node(bst_node_t *root, const char *key, assoc_array_error_t *err);

// Освобождение памяти
void bst_free(bst_node_t *root);

// Поиск минимального элемента в дереве
bst_node_t *bst_find_min_node(bst_node_t *root);

// Поиск максимального элемента в дереве
bst_node_t *bst_find_max_node(bst_node_t *root);

// Применение функции к каждому элементу в дереве
void bst_foreach(bst_node_t *root, void (*action)(const char *key, int *num, void *param), void *param);

#endif
