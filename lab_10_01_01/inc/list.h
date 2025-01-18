#ifndef LIST_H__
#define LIST_H__

#include "node.h"

int list_read(const char *filename, node_t **head);

int list_print(const char *filename, struct node *head);

void list_free(node_t *head);

void *pop_front(node_t **head);

void append(node_t **head_a, node_t **head_b);

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));

#endif
