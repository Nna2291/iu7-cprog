#include "list.h"
#include "errors.h"

#include <stdio.h>

void list_add_to_end(node_t **head, node_t *node_to_add)
{
    node_t *cur = *head;
    if (!*head)
    {
        *head = node_to_add;
        return;
    }
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = node_to_add;
}

void list_free(node_t *head)
{
    node_t *cur = head, *next = NULL;
    while (cur)
    {
        next = cur->next;
        destroy_node(cur);
        cur = next;
    }
}

void list_print(node_t *head)
{
    if (!head)
    {
        printf("Empty list\n");
        return;
    }
    while (head)
    {
        printf("%d %d ", head->coefficient, head->power);
        head = head->next;
    }
    printf("L\n");
}


int list_read(node_t **head)
{
    int power, coefficient;

    do 
    {
        if (scanf("%d %d", &coefficient, &power) != 2)
        {
            list_free(*head);
            return ERR_IO;
        }

        node_t *node_tmp = create_node(power, coefficient);
        if (!node_tmp)
        {
            list_free(*head);
            return ERR_MEM;
        }
        list_add_to_end(head, node_tmp);
    }
    while (power != 0);

    return ERR_OK;
}
