#include <stdlib.h>
#include <stdio.h>

#include "node.h"
#include "dino.h"

node_t *node_create(dino_t *dino)
{
    if (!dino)
    {
        return NULL;
    }
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->data = dino;
        node->next = NULL;
    }
    else
        return NULL;
    return node;
}

void node_destroy(node_t *node)
{
    dino_free_content(node->data);
    free(node->data);
    free(node);
}

int node_print(FILE *f, const node_t *node)
{
    int rc = print_dino(f, (dino_t*) ((node)->data));
    return rc;
}
