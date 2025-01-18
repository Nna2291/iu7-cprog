#include "compare.h"
#include "constants.h"
#include <math.h>
#include <stdbool.h>

static bool double_eq(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}

int compare_matrix(const double **mtr1, size_t n1, size_t m1, const double **mtr2, size_t n2, size_t m2)
{
    if ((n1 != n2) || (m1 != m2))
    {
        return 1;
    }
    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            if (!double_eq(mtr1[i][j], mtr2[i][j], EPSILON))
            {
                return 0;
            }
        }
    }
    return 1;
}
