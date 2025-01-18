#include "calculate.h"
#include "list.h"
#include "errors.h"
#include "node.h"

#include <stddef.h>
#include <math.h>

int calculate_val(const node_t *head, int a, int *val)
{
    if (!head || !val)
    {
        return ERR_ARGS;
    }
    
    int tmp_val = 0;

    while (head != NULL)
    {
        tmp_val += head->coefficient * pow(a, head->power);
        head = head->next;    
    }

    *val = tmp_val;
    return ERR_OK;
}

int calculate_derivative(const node_t *head, node_t **new_head)
{
    if (!head || !new_head)
    {
        return ERR_ARGS;
    }
    
    node_t *derivative_head = NULL;
    while (head->next != NULL)
    {   
        node_t *derivative_node = create_node((head->power) - 1, (head->power) * (head->coefficient));
        if (!derivative_node)
        {
            list_free(derivative_head);
            return ERR_MEM;
        }
        list_add_to_end(&derivative_head, derivative_node);
        head = head->next;
    }

    *new_head = derivative_head;
    return ERR_OK;
}

int calculate_sum(const node_t *head1, const node_t *head2, node_t **head3)
{
    if (!head1 || !head2 || !head3)
    {
        return ERR_ARGS;
    }

    node_t *new_head = NULL, *new_node = NULL;
    
    while (head1 && head2)
    {
        int new_power, new_coefficient;

        if (head1->power > head2->power)
        {
            new_power = head1->power;
            new_coefficient = head1->coefficient;
            head1 = head1->next;
        }
        else if (head1->power < head2->power)
        {
            new_power = head2->power;
            new_coefficient = head2->coefficient;
            head2 = head2->next;
        }
        else
        {
            new_power = head1->power;
            new_coefficient = head1->coefficient + head2->coefficient;
            head1 = head1->next;
            head2 = head2->next;
        }

        new_node = create_node(new_power, new_coefficient);
        if (!new_node)
        {
            list_free(new_head);
            return ERR_MEM;
        }
        list_add_to_end(&new_head, new_node);
    }

    while (head1)
    {
        new_node = create_node(head1->power, head1->coefficient);
        if (!new_node)
        {
            list_free(new_head);
            return ERR_MEM;
        }
        list_add_to_end(&new_head, new_node);
        head1 = head1->next;
    }

    while (head2)
    {
        new_node = create_node(head2->power, head2->coefficient);
        if (!new_node)
        {
            list_free(new_head);
            return ERR_MEM;
        }
        list_add_to_end(&new_head, new_node);
        head2 = head2->next;
    }

    *head3 = new_head;
    return ERR_OK;
}

int divide_poly(const node_t *head, node_t **head_odd, node_t **head_even)
{
    if (!head || !head_odd || !head_even)
    {
        return ERR_ARGS;
    }

    node_t *new_node = NULL;

    while (head)
    {
        new_node = create_node(head->power, head->coefficient);
        if (!new_node)
        {
            list_free(*head_odd);
            list_free(*head_even);
            return ERR_MEM;
        }

        if (head->power % 2 == 0)
        {   
            list_add_to_end(head_even, new_node);
        }
        else
        {
            list_add_to_end(head_odd, new_node);
        }
        head = head->next;
    }
    return ERR_OK;
}
