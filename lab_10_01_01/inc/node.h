#ifndef NODE_H__
#define NODE_H__

#include "dino.h"

typedef struct node node_t;

struct node
{
    void *data;
    struct node *next;
};

struct node *node_create(dino_t *dino);

void node_destroy(struct node *node);

int node_print(FILE *f, const struct node *node);

#endif
