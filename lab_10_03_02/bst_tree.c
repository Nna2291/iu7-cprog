#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>

#include "bst_tree.h"

static bst_node_t *create_node(const char *key, int value)
{
    bst_node_t *node = malloc(sizeof(bst_node_t));
    if (!node)
    {
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;

    node->key = strdup(key);
    if (!node->key)
    {
        free(node);
        return NULL;
    }
    node->value = value;

    return node;
}

bst_node_t *bst_insert_node(bst_node_t *root, const char *key, int value, assoc_array_error_t *err)
{
    if (!key || strlen(key) == 0 || !err)
    {
        *err = ASSOC_ARRAY_INVALID_PARAM;
        return root;
    }

    if (!root)
    {
        bst_node_t *new_node = create_node(key, value);
        if (!new_node)
        {
            *err = ASSOC_ARRAY_MEM;
            return NULL;
        }
        *err = ASSOC_ARRAY_OK;
        return new_node;
    }

    int cmp = strcmp(key, root->key);

    if (cmp == 0)
    {
        *err = ASSOC_ARRAY_KEY_EXISTS;
        return root;
    }
    else if (cmp < 0)
    {
        root->left = bst_insert_node(root->left, key, value, err);
    }
    else
    {
        root->right = bst_insert_node(root->right, key, value, err);
    }

    return root;
}

bst_node_t *bst_find_node(bst_node_t *root, const char *key)
{
    if (!root || !key || strlen(key) == 0)
    {
        return NULL;
    }

    int cmp = strcmp(key, root->key);

    if (cmp == 0)
    {
        return root;
    }
    else if (cmp < 0)
    {
        return bst_find_node(root->left, key);
    }
    else
    {
        return bst_find_node(root->right, key);
    }
}

bst_node_t *bst_find_min_node(bst_node_t *root)
{
    if (!root)
    {
        return NULL;
    }

    while (root->left)
    {
        root = root->left;
    }
    return root;
}

bst_node_t *bst_find_max_node(bst_node_t *root)
{
    if (!root)
    {
        return NULL;
    }

    while (root->right)
    {
        root = root->right;
    }
    return root;
}

bst_node_t *bst_remove_node(bst_node_t *root, const char *key, assoc_array_error_t *err)
{
    if (!root || !key || strlen(key) == 0)
    {
        *err = ASSOC_ARRAY_NOT_FOUND;
        return NULL;
    }

    int cmp = strcmp(key, root->key);

    if (cmp < 0)
    {
        root->left = bst_remove_node(root->left, key, err);
    }
    else if (cmp > 0)
    {
        root->right = bst_remove_node(root->right, key, err);
    }
    else
    {
        if (!root->left && !root->right)
        {
            free(root->key);
            free(root);
            *err = ASSOC_ARRAY_OK;
            return NULL;
        }
        else if (!root->left)
        {
            bst_node_t *tmp = root->right;
            free(root->key);
            free(root);
            *err = ASSOC_ARRAY_OK;
            return tmp;
        }
        else if (!root->right)
        {
            bst_node_t *tmp = root->left;
            free(root->key);
            free(root);
            *err = ASSOC_ARRAY_OK;
            return tmp;
        }
        else
        {
            bst_node_t *min_in_right = bst_find_min_node(root->right);
            
            free(root->key);
            root->key = strdup(min_in_right->key);
            if (!root->key)
            {
                *err = ASSOC_ARRAY_MEM;
                return NULL;
            }
            root->value = min_in_right->value;

            root->right = bst_remove_node(root->right, min_in_right->key, err);
        }
    }

    return root;
}

void bst_foreach(bst_node_t *root, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!root)
    {
        return;
    }
    bst_foreach(root->left, action, param);
    action(root->key, &root->value, param);
    bst_foreach(root->right, action, param);
}

void bst_free(bst_node_t *root)
{
    if (!root)
    {
        return;
    }
    bst_free(root->left);
    bst_free(root->right);

    free(root->key);
    root->key = NULL;
    free(root);
}
