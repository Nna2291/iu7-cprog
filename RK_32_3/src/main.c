#include "node.h"
#include "list.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define ARG_LEN 3
#define FILE_ARG_INDEX 1
#define FILE_INT_INDEX 2
#define BASE 10

bool is_int(const char* str)
{
    const char *digits = "0123456789";

    for (size_t i = 0; i < strlen(str); i++)
    {
        if (!(strchr(digits, str[i])))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return ERR_ARGS;
    }

    char *end;
    long del_value = strtol(argv[FILE_INT_INDEX], &end, BASE);
    if (del_value == LONG_MIN || del_value == LONG_MAX || *end != '\0')
    {
        return ERR_ARGS;
    }
    node_t *head = NULL;
    int rc = list_read_from_file(argv[FILE_ARG_INDEX], &head);
    if (rc == ERR_OK)
    {
        int del_value = atoi(argv[FILE_INT_INDEX]);
        list_print(head);
        delete_values(&head, del_value);
        list_print(head);
        list_free(head);
    }
    return rc;
}

