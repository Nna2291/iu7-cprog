#include "errors.h"
#include "arr_io.h"
#include "arr_op.h"
#include <stdlib.h>

int main(void)
{
    int rc = ERR_OK;

    int *arr1 = NULL, *arr2 = NULL, *arr3 = NULL, *set1 = NULL, *set2 = NULL;
    size_t n1 = 0, n2 = 0, n3 = 0, n_set1 = 0, n_set2 = 0;

    rc = input_array(&arr1, &n1);
    if (rc == ERR_OK)
    {
        rc = array_to_set(arr1, n1, &set1, &n_set1);
    }
    if (rc == ERR_OK)
    {
        rc = input_array(&arr2, &n2);
    }
    if (rc == ERR_OK)
    {
        rc = array_to_set(arr2, n2, &set2, &n_set2);
    }

    if (rc == ERR_OK)
    {
        rc = array_unioin(arr1, n1, arr2, n2, &arr3, &n3);
    }

    if (rc == ERR_OK)
    {
        printf("Set 1\n");
        print_array(set1, n_set1);
        printf("Set 2\n");
        print_array(set2, n_set2);
        printf("Op\n");
        print_array(arr3, n3);
    }

    free(arr1);
    free(set1);
    free(arr2);
    free(set2);
    free(arr3);
    return rc;
}
