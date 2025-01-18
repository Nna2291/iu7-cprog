#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"
#include "array_io.h"
#include "array_loc.h"
#include "constants.h"
#include "errors.h"

int main(int argc, char **argv)
{
    if (argc != ARGS_COUNT_NO_KEY && argc != ARGS_COUNT_WITH_KEY)
    {
        return ERR_ARGS;
    }

    int *arr_b = NULL, *arr_e = NULL;
    int *new_arr_b = NULL, *new_arr_e = NULL;

    bool key_func = (argc == 4);
    bool key_correct;

    if (key_func)
    {
        key_correct = (strcmp(argv[3], "f") == 0);
    }
    else
    {
        key_correct = false;
    }

    FILE *f = fopen(argv[1], "r");

    if (!f)
    {
        return ERR_IO;
    }

    int rc = create_array(f, &arr_b, &arr_e);
    fclose(f);

    if (rc == ERR_OK)
    {
        if (key_func && key_correct)
        {
            rc = key(arr_b, arr_e, &new_arr_b, &new_arr_e);
            if (rc == ERR_OK)
            {
                mysort(new_arr_b, new_arr_e - new_arr_b, sizeof(int), &int_cmp);
                rc = write_array(argv[2], new_arr_b, new_arr_e);
            }
        }
        else if (key_func && !key_correct)
        {
            rc = ERR_ARGS;
        }
        else
        {
            mysort(arr_b, arr_e - arr_b, sizeof(int), &int_cmp);
            rc = write_array(argv[2], arr_b, arr_e);
        }
    }

    array_free(arr_b);
    array_free(new_arr_b);

    return rc;
}
