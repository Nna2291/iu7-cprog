#include <string.h>

#include "item.h"
#include "item_array.h"

#include "errors.h"

#define ALL_STRING "ALL"
#define ARG_COUNT_SUBSTR 3
#define ARG_COUNT_NO_SUBSTR 2
#define ARG_FILE_INDEX 1
#define ARG_SUBSTR_INDEX 2

int main(int argc, char **argv)
{
    FILE *f;
    item_t *items = NULL;

    size_t items_n = 0;
    int rc = ERR_OK;

    if (argc != ARG_COUNT_NO_SUBSTR && argc != ARG_COUNT_SUBSTR)
    {
        printf("USAGE: app.exe file_name [substring]\n");
        return ERR_ARGS;
    }

    f = fopen(argv[ARG_FILE_INDEX], "r");
    if (!f)
    {
        return ERR_IO;
    }

    rc = create_array(f, &items, &items_n);
    // printf("%zu\n", items_n);
    
    if (argc == ARG_COUNT_NO_SUBSTR && rc == ERR_OK)
    {
        sort_array(items, items_n);
        print_items(items, items_n);
    }

    if (argc == ARG_COUNT_SUBSTR && rc == ERR_OK)
    {
        if (strcmp(argv[ARG_SUBSTR_INDEX], ALL_STRING) != 0)
        {
            print_items_with_substr(items, items_n, argv[ARG_SUBSTR_INDEX]);
        }
        else
        {
            print_items(items, items_n);
        }
    }

    fclose(f);
    
    item_array_free(items, items_n);
    return rc;
}
