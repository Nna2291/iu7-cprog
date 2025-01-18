#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "associative_array.h"

typedef struct assoc_node
{
    char *key;
    int value;
    struct assoc_node *next;
} assoc_node_t;

struct assoc_array_type
{
    assoc_node_t *head;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(assoc_array_t));
    if (arr)
    {
        arr->head = NULL;
    }
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr || !*arr)
    {
        return;
    }

    assoc_node_t *head = (*arr)->head;
    while (head)
    {
        assoc_node_t *tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp);
    }

    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_node_t *head = arr->head;
    while (head)
    {
        if (strcmp(head->key, key) == 0)
        {
            return ASSOC_ARRAY_KEY_EXISTS;
        }
        head = head->next;
    }

    assoc_node_t *new_node = malloc(sizeof(assoc_node_t));
    if (!new_node)
    {
        return ASSOC_ARRAY_MEM;
    }

    new_node->key = strdup(key);
    if (!new_node->key)
    {
        free(new_node);
        return ASSOC_ARRAY_MEM;
    }

    new_node->value = num;
    new_node->next = arr->head;
    arr->head = new_node;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || !num || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_node_t *head = arr->head;
    while (head)
    {
        if (strcmp(head->key, key) == 0)
        {
            *num = &head->value;
            return ASSOC_ARRAY_OK;
        }
        head = head->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_node_t **head = &arr->head;
    while (*head)
    {
        if (strcmp((*head)->key, key) == 0)
        {
            assoc_node_t *temp = *head;
            *head = (*head)->next;
            free(temp->key);
            free(temp);
            return ASSOC_ARRAY_OK;
        }
        head = &(*head)->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_node_t *head = arr->head;
    while (head)
    {
        assoc_node_t *temp = head;
        head = head->next;
        free(temp->key);
        free(temp);
    }

    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_node_t *head = arr->head;
    while (head)
    {
        action(head->key, &head->value, param);
        head = head->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    if (!arr->head)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    assoc_node_t *head = arr->head;
    assoc_node_t *min_node = head;
    while (head)
    {
        if (strcmp(head->key, min_node->key) < 0)
        {
            min_node = head;
        }
        head = head->next;
    }

    *num = &min_node->value;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    if (!arr->head)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    assoc_node_t *head = arr->head;
    assoc_node_t *max_node = head;
    while (head)
    {
        if (strcmp(head->key, max_node->key) > 0)
        {
            max_node = head;
        }
        head = head->next;
    }

    *num = &max_node->value;
    return ASSOC_ARRAY_OK;
}
