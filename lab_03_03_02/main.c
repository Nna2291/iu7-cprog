#include "io.h"
#include "logic.h"
#include "errors.h"

int main(void)
{
    int matrix[N][M];
    size_t n, m;
    int rc = matrix_input(matrix, &n, &m);
    if (rc != ERR_OK)
    {
        return rc;
    }
    sort_matrix(matrix, n, m);
    print_matrix((const int (*)[M]) matrix, n, m);
    return ERR_OK;
}

