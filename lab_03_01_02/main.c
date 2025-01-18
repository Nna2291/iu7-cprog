#include "io.h"
#include "logic.h"
#include "errors.h"

int main(void)
{
    int matrix[N][M];
    int arr[M];
    size_t n, m;
    int rc = matrix_input(matrix, &n, &m);
    if (rc != ERR_OK)
    {
        return rc;
    }
    fill_array((const int (*)[M]) matrix, arr, n, m);
    print_array(arr, m);
    return ERR_OK;
}

