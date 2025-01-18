#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "item.h"
#include "item_array.h"

int items_count(FILE *f, size_t *n)
{
    item_t item_tmp = { NULL, 0.0, 0.0, 0.0 };
    
    size_t i = 0;
    int rc = ERR_OK;
    
    while (!feof(f) && rc == ERR_OK)
    {
        rc = item_read(f, &item_tmp);
        if (rc == ERR_OK)
        {
            i += 1;
        }
        else
        {
            item_free_content(&item_tmp);
            return ERR_IO;
        }
        item_free_content(&item_tmp);
    }
    
    *n = i;
    return rc;
}

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

int item_array_read(FILE *f, item_t *array, size_t n)
{
    int rc = ERR_OK;
    // item_t item_tmp = { NULL, 0.0, 0.0, 0.0 };

    for (size_t i = 0; i < n; i++)
    {
        rc = item_read(f, &array[i]);
        if (rc != ERR_OK)
        {
            item_array_free(array, n);
            return rc;
        }
        // // rc = item_copy(&array[i], &item_tmp);
        // if (rc != ERR_OK)
        //     return rc;
        // item_free_content(&item_tmp);
    }
    return rc;
}

void item_array_free(item_t *item_arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        item_free_content(&item_arr[i]);
    }
    free(item_arr);
}

int create_array(FILE *f, item_t **array, size_t *n)
{
    item_t *ptmp;
    size_t ntmp = 0;
    int rc;
    *array = NULL;
    *n = 0;

    rc = items_count(f, &ntmp);
    if (rc != ERR_OK)
    {
        return rc;
    }
    ptmp = calloc(ntmp, sizeof(item_t));
    if (ptmp)
    {
        rewind(f);
        rc = item_array_read(f, ptmp, ntmp);
        if (rc == ERR_OK)
        {
            *array = ptmp;
            *n = ntmp;
        }
        else
        {
            item_array_free(*array, ntmp);
        }
    }
    else
    {
        rc = ERR_MEMORY;
    }
    return rc;
}

void print_items_with_substr(const item_t *array, size_t n, const char *substring)
{
    bool was_first_printed = false;
    for (size_t i = 0; i < n; i++)
    {
        if (item_substr(&array[i], substring))
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

