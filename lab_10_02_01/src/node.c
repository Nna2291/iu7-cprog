#include <stdlib.h>
#include "node.h"

node_t *create_node(int power, int coefficient)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
    {
        return NULL;
    }

    node->power = power;
    node->coefficient = coefficient;
    node->next = NULL;
    return node;
}

void destroy_node(node_t *cur)
{
    free(cur);
}
