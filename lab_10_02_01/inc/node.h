#ifndef NODE_H__
#define NODE_H__

typedef struct node node_t;

struct node
{
    int power;
    int coefficient;
    node_t *next;
};

node_t *create_node(int power, int coefficient);

void destroy_node(node_t *cur);


#endif
