#ifndef NODE_H__
#define NODE_H__

typedef struct node node_t;

struct node
{
    int val;
    node_t *next;
};

node_t *create_node(int val);

void destroy_node(node_t *cur);

#endif
