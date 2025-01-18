#include "list.h"
#include "errors.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

static node_t *list_add_tail(node_t *head, node_t *node)
{
    if (!head)
    {
        return node;
    }

    node_t *last = head;
    while (last->next)
    {
        last = last->next;
    }

    last->next = node;

    return head;
}

static int list_read_ex(FILE *f, node_t **head)
{
    node_t *node;
    node_t *head_tmp = NULL;
    dino_t *dino_tmp = NULL;
    int rc = ERR_OK;
    while (!feof(f) && ((dino_tmp = dino_read(f, &rc)) != NULL))
    {
        node = node_create(dino_tmp);
        if (node)
            head_tmp = list_add_tail(head_tmp, node);
        else
        {
            list_free(head_tmp);
            return ERR_MEM;
        }
    }
    *head = head_tmp;
    return rc;
}

int list_read(const char *filename, node_t **head)
{
    FILE *f = fopen(filename, "r");

    if (!f)
    {
        return ERR_IO;
    }

    int rc = list_read_ex(f, head);

    fclose(f);
    return rc;
}

int list_print(const char *filename, node_t *head)
{
    node_t *cur = head;
    FILE *f = fopen(filename, "w");
    int rc = ERR_OK;
    while (cur)
    {
        rc = node_print(f, cur);
        cur = cur->next;
    }
    fclose(f);
    return rc;
}

void list_free(node_t *head)
{
    node_t *cur = head, *next;

    while (cur)
    {
        next = cur->next;
        node_destroy(cur);
        cur = next;
    }
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    while (head)
    {
        if (comparator(head->data, data) == 0)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void *pop_front(node_t **head)
{
    if (!head || !*head)
    {
        return NULL;
    }

    node_t *tmp = *head;
    void *data = tmp->data;

    *head = tmp->next;

    free(tmp);
    return data;
}

void append(node_t **head_a, node_t **head_b)
{
    node_t *node;
    void *dino_tmp;
    do
    {
        dino_tmp = pop_front(head_b);
        node = node_create(dino_tmp);
        if (node)
            *head_a = list_add_tail(*head_a, node);
    }
    while (dino_tmp);
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (!head || !element)
    {
        return;
    }

    if (!*head || comparator(element->data, (*head)->data) <= 0)
    {
        element->next = *head;
        *head = element;
        return;
    }

    node_t *cur = *head;
    while (cur->next && comparator(element->data, cur->next->data) > 0)
    {
        cur = cur->next;
    }

    element->next = cur->next;
    cur->next = element;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (!head || !head->next)
    {
        return head;
    }

    node_t *sorted = NULL;
    node_t *cur = head;

    while (cur)
    {
        node_t *next = cur->next;
        cur->next = NULL;
        sorted_insert(&sorted, cur, comparator);
        cur = next;
    }

    return sorted;
}
