#include "io.h"
#include "logic.h"
#include "errors.h"


int main(void)
{
    int matrix[N][M];
    int answer = 0, rc;
    size_t n, m;
    rc = matrix_input(matrix, &n, &m);
    if (rc != ERR_OK)
    {
        return rc;
    }
    if (n != m)
    {
        return ERR_IO;
    }
    rc = find_maximum_value((const int (*)[M]) matrix, n, &answer);
    if (rc != ERR_OK)
    {
        return rc;
    }
    print_value(answer);
    return ERR_OK;
}

