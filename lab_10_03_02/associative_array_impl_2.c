#include <stdlib.h>
#include <string.h>
#include "associative_array.h"
#include "bst_tree.h"

struct assoc_array_type
{
    bst_node_t *root;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(assoc_array_t));
    if (!arr)
    {
        return NULL;
    }
    arr->root = NULL;
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr || !(*arr))
    {
        return;
    }
    bst_free((*arr)->root);
    free(*arr);
    
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_array_error_t err = ASSOC_ARRAY_OK;
    arr->root = bst_insert_node(arr->root, key, num, &err);
    return err;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || strlen(key) == 0 || !num)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    bst_node_t *node = bst_find_node(arr->root, key);
    if (!node)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    *num = &node->value;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_array_error_t err = ASSOC_ARRAY_OK;
    arr->root = bst_remove_node(arr->root, key, &err);
    return err;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    bst_free(arr->root);
    arr->root = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    bst_foreach(arr->root, action, param);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    bst_node_t *node = bst_find_min_node(arr->root);
    if (!node)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }
    *num = &node->value;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    bst_node_t *node = bst_find_max_node(arr->root);
    if (!node)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    *num = &node->value;
    return ASSOC_ARRAY_OK;
}