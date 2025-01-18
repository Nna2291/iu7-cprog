#include <string.h>

#include "item.h"
#include "item_array.h"

#include "errors.h"

#define ALL_STRING "ALL"

int main(int argc, char **argv)
{
    FILE *f;
    item_t items[N_MAX];

    size_t items_n = 0;
    int rc = ERR_OK;

    if (argc != 2 && argc != 3)
    {
        printf("USAGE: app.exe file_name [substring]\n");
        return ERR_ARGS;
    }

    f = fopen(argv[1], "r");
    if (!f)
    {
        return ERR_IO;
    }

    rc = read_array(f, items, &items_n, N_MAX);
    // printf("%zu\n", items_n);
    
    if (argc == 2 && rc == ERR_OK)
    {
        sort_array(items, items_n);
        print_items(items, items_n);
    }

    if (argc == 3 && rc == ERR_OK)
    {
        if (strcmp(argv[2], ALL_STRING) != 0)
        {
            print_items_with_substr(items, items_n, argv[2]);
        }
        else
        {
            print_items(items, items_n);
        }
    }

    fclose(f);
    return rc;
}
