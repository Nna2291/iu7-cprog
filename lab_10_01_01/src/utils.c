#include "utils.h"
#include <math.h>

int compare_double(double a, double b, double eps)
{
    if (fabs(a - b) < eps)
    {
        return 0;
    }
    else if ((a - b) > eps)
    {
        return 1;
    }
    return -1;
}