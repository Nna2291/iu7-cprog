#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "item.h"

static void swap(item_t *xp, item_t *yp)
{
    item_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_array(item_t *array, size_t n)
{
    if (n < 2)
        return;

    bool swapped = false;
    
    while (!swapped) 
    {
        swapped = true;
        for (size_t i = 0; i < n - 1; i++) 
        {
            if (item_cmp(&array[i], &array[i + 1]) == 1) 
            {
                swap(&array[i], &array[i + 1]);
                swapped = false;
            }
        }
    }
}

void print_items(const item_t *array, size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        item_print(&array[i]);
        printf("\n");
    }
    item_print(&array[n - 1]);
}

int read_array(FILE *f, item_t *array, size_t *n, size_t n_max)
{
    int rc = ERR_OK;
    size_t index = 0;

    while (!feof(f))
    {
        if (index == n_max)
        {
            return ERR_OVERFLOW;
        }
        rc = item_read(f, &array[index]);

        if (rc != ERR_OK)
        {
            return rc;
        }
        index++;
    }

    *n = index; 

    return rc;
}

// int read_array(FILE *f, item_t *array, size_t *n, size_t n_max)
// {
//     int rc = ERR_OK;
//     size_t index = 0;

//     while (!feof(f))
//     {
//         if (index == n_max)
//         {
//             return ERR_OVERFLOW;
//         }

//         rc = item_read(f, &array[index]);

//         if (rc != ERR_OK)
//         {
//             return rc;
//         }
//         index++;
//     }

//     *n = index; 

//     return rc;
// }


void print_items_with_substr(const item_t *array, size_t n, const char *substring)
{
    bool was_first_printed = false;
    for (size_t i = 0; i < n; i++)
    {
        if (strncmp(substring, array[i].title, strlen(substring)) == 0)
        {
            if (!was_first_printed)
            {
                item_print(&array[i]);
                was_first_printed = true;
            } 
            else
            {
                printf("\n");
                item_print(&array[i]);
            }
        }
    }
}
