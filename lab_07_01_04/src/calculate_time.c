#include <math.h>
#include "calculate_time.h"
#include "errors.h"

double calc_rse(FILE *f)
{
    if (!f)
    {
        printf("FILE ERROR\n");
        return ERR_IO;
    }

    double t_sum = 0;
    int size = 0;
    int value;

    rewind(f);

    while (fscanf(f, "%d", &value) == 1)
    {
        t_sum += value;
        size++;
    }

    double t_avg = t_sum / size;
    double s_sum = 0;

    rewind(f);

    while (fscanf(f, "%d", &value) == 1)
    {
        s_sum += (value - t_avg) * (value - t_avg);
    }
    
    double dispersion = s_sum / (size - 1);
    double std_dev = sqrt(dispersion);
    double std_err = std_dev / sqrt(size);
    double rse = (std_err / t_avg) * 100;

    return rse;
}

double calc_avg(FILE *f)
{
    if (!f)
    {
        printf("FILE ERROR\n");
        return ERR_IO;
    }

    rewind(f);

    double t_sum = 0;
    int size = 0;
    int value;
    while (fscanf(f, "%d", &value) == 1)
    {
        t_sum += value;
        size++;
    }
    return t_sum / size;
}
