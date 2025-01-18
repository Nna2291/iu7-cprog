#ifndef LIST_H__
#define LIST_H__

#include "node.h"

void list_free(node_t *head);

void list_add_to_end(node_t **head, node_t *node_to_add);

void list_print(node_t *head);

void delete_values(node_t **head, int val);

int list_read_from_file(const char *filename, node_t **head);

#endif
