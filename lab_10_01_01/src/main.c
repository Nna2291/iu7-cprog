#include "list.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGS_APPEND 5
#define ARGS_SORT 4

#define ARGS_INDEX_COMMAND 1
#define ARGS_INDEX_FILE_1 2
#define ARGS_INDEX_FILE_2 3
#define ARGS_INDEX_FILE_OUT_APPEND 4
#define ARGS_INDEX_FILE_OUT 3
#define ARGS_COMMAND_SORT "s"
#define ARGS_COMMAND_APPEND "a"


int main(int argc, char **argv)
{
    // app.exe [s,a] file1 [file2] outfile
    int rc = ERR_OK;
    if (argc != ARGS_APPEND && argc != ARGS_SORT)
    {
        return ERR_ARGS;
    }

    if (argc == ARGS_SORT)
    {
        node_t *head = NULL;
        if (strcmp(argv[ARGS_INDEX_COMMAND], ARGS_COMMAND_SORT) == 0)
        {
            rc = list_read(argv[ARGS_INDEX_FILE_1], &head);
            node_t *head_sorted = sort(head, comparator);
            rc = list_print(argv[3], head_sorted);
        }
        list_free(head);
    }
    else if (argc == ARGS_APPEND)
    {
        node_t *head_a = NULL;
        node_t *head_b = NULL;
        int rc1 = ERR_OK;
        rc = list_read(argv[ARGS_INDEX_FILE_1], &head_a);
        if (rc == ERR_OK)
        {
            rc1 = list_read(argv[ARGS_INDEX_FILE_2], &head_b);
        }
        else
        {
            rc = ERR_IO;
        }
        if (rc1 == ERR_OK && strcmp(argv[ARGS_INDEX_COMMAND], ARGS_COMMAND_APPEND) == 0)
        {
            append(&head_a, &head_b);
            rc = list_print(argv[ARGS_INDEX_FILE_OUT_APPEND], head_a);
        }
        list_free(head_a);
        list_free(head_b);
    }
    
    return rc;
}
