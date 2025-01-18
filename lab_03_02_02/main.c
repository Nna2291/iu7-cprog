#include "io.h"
#include "logic.h"
#include "errors.h"

int main(void)
{
    int matrix[N_INPUT][M_INPUT];
    size_t n, m;
    int rc = matrix_input(matrix, &n, &m);

    if (rc != ERR_OK)
    {
        return rc;
    }

    analyse_rows(matrix, &n, m);
    print_matrix((const int (*)[M_INPUT]) matrix, n, m);
    return ERR_OK;
}

