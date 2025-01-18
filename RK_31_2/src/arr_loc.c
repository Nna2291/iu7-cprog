#include "arr_loc.h"
#include <stdlib.h>

int *arr_loc(size_t n)
{
    int *temp = NULL;
    temp = calloc(n, sizeof(int));
    if (!temp)
    {
        return NULL;
    }
    return temp;
}
