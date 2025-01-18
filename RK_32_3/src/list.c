#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "errors.h"

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
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

void delete_values(node_t **head, int val)
{
    node_t *cur = *head;
    node_t *prev = NULL;

    while (cur)
    {
        if (cur->val > val)
        {
            node_t *tmp_adr = cur;
            if (prev)
            {
                prev->next = cur->next;
            }
            else
            {
                *head = cur->next;
            }
            cur = cur->next;
            destroy_node(tmp_adr);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

static int list_read_digit(FILE *f, node_t **head)
{
    int val = 0;
    if (fscanf(f, "%d ", &val) != 1)
    {
        list_free(*head);
        return ERR_IO;
    }
    node_t *node_tmp = create_node(val);
    if (!node_tmp)
    {
        list_free(*head);
        return ERR_MEM;
    }
    list_add_to_end(head, node_tmp);
    return ERR_OK;
}

int list_read_from_file(const char *filename, node_t **head)
{
    FILE *f = fopen(filename, "r");
    int rc = ERR_OK;

    if (!f)
    {
        return ERR_IO;
    }

    while (rc == ERR_OK && !feof(f))
    {
        rc = list_read_digit(f, head);
    }
    fclose(f);
    return rc;
}
