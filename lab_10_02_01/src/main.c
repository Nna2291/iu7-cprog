#include "list.h"
#include "errors.h"
#include "calculate.h"
#include "node.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define COMMAND_LEN 3
#define BUFFER (COMMAND_LEN + 1)

#define COMMAND_VALUE "val"
#define COMMAND_DERIVATIVE "ddx"
#define COMMAND_SUM "sum"
#define COMMAND_DIVIDE "dvd"

int main(void)
{
    char command[BUFFER];

    if (!fgets(command, sizeof(command), stdin))
    {
        return ERR_IO;
    }

    if (strcmp(command, COMMAND_VALUE) == 0)
    {
        node_t *head = NULL;
        int rc = list_read(&head), a, val;

        if (rc != ERR_OK)
        {
            return rc;
        }

        if (scanf("%d", &a) != 1)
        {
            list_free(head);
            return ERR_IO;
        }

        rc = calculate_val(head, a, &val);
        if (rc != ERR_OK)
        {
            list_free(head);
            return rc;
        }

        printf("%d\n", val);
        list_free(head);
    }
    else if (strcmp(command, COMMAND_DERIVATIVE) == 0)
    {
        node_t *head = NULL;
        node_t *derivative_head = NULL;
        int rc = list_read(&head);

        if (rc != ERR_OK)
        {
            return rc;
        }

        rc = calculate_derivative(head, &derivative_head);
        if (rc != ERR_OK)
        {
            list_free(head);
            return rc;
        }

        list_print(derivative_head);
        list_free(head);
        list_free(derivative_head);
    }
    else if (strcmp(command, COMMAND_SUM) == 0)
    {
        node_t *head1 = NULL, *head2 = NULL, *head3 = NULL;
        
        int rc = list_read(&head1);
        if (rc != ERR_OK)
        {
            return rc;
        }

        rc = list_read(&head2);
        if (rc != ERR_OK)
        {
            list_free(head1);
            return rc;
        }

        rc = calculate_sum(head1, head2, &head3);
        if (rc != ERR_OK)
        {
            list_free(head1);
            list_free(head2);
            return rc;
        }

        list_print(head3);
        list_free(head1);
        list_free(head2);
        list_free(head3);
    }
    else if (strcmp(command, COMMAND_SUM) == 0)
    {
        node_t *head1 = NULL, *head2 = NULL, *head3 = NULL;
        
        int rc = list_read(&head1);
        if (rc != ERR_OK)
        {
            return rc;
        }

        rc = list_read(&head2);
        if (rc != ERR_OK)
        {
            list_free(head1);
            return rc;
        }

        rc = calculate_sum(head1, head2, &head3);
        if (rc != ERR_OK)
        {
            list_free(head1);
            list_free(head2);
            return rc;
        }

        list_print(head3);
        list_free(head1);
        list_free(head2);
        list_free(head3);
    }
    else if (strcmp(command, COMMAND_DIVIDE) == 0)
    {
        node_t *head1 = NULL, *head_odd = NULL, *head_even = NULL;

        int rc = list_read(&head1);
        if (rc != ERR_OK)
        {
            return rc;
        }

        rc = divide_poly(head1, &head_odd, &head_even);
        if (rc != ERR_OK)
        {
            list_free(head_odd);
            list_free(head_even);
            return rc;
        }

        list_print(head_even);
        list_print(head_odd);
        list_free(head1);
        list_free(head_odd);
        list_free(head_even);
    }
    else
    {
        return ERR_ARGS;
    }


    return ERR_OK;
}