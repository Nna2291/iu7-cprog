#include "io.h"
#include "logic.h"
#include "errors.h"

int main(void)
{
    int matrix[N][M];
    int array[M * N];
    int rc, size;
    size_t n, m;
    rc = matrix_input(matrix, &n, &m);
    if (rc != ERR_OK)
    {
        return rc;
    }
    size = put_primes(array, (const int (*)[M]) matrix, n, m);

    if (size == 0)
    {
        return ERR_EMPTY;
    }

    reverse_array(array, size);
    put_back_in_matrix(array, matrix, n, m);

    print_matrix((const int (*)[M]) matrix, n, m);
    return 0;
}

