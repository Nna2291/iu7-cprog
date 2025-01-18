#ifndef LIST_H__
#define LIST_H__

#include "node.h"

void list_free(node_t *head);

void list_add_to_end(node_t **head, node_t *node_to_add);

void list_print(node_t *head);

int list_read(node_t **head);

#endif
