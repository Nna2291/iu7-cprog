#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "sorting.h"
#include "calculate_time.h"
#include "errors.h"

#define RSE_IDEAL 1

#ifndef N
#define N 1
#endif

#ifndef F
#define F -1
#endif

#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW -1
#endif

#ifndef NULL
#define NULL -1
#endif

#ifndef ERR_IO
#define ERR_IO 1
#endif

#ifndef ERR_OK
#define ERR_OK 0
#endif

static unsigned long long time_calc(const struct timespec *beg, const struct timespec *end)
{
    unsigned long long sec_diff = (end->tv_sec - beg->tv_sec) * 1000000000ull;
    unsigned long long nsec_diff = end->tv_nsec - beg->tv_nsec;
    unsigned long long total_time = sec_diff + nsec_diff;
    return total_time;
}

int main(void)
{
    int a[N], b[N];
    FILE *fq, *fm;

    unsigned long long sort_duration_q, sort_duration_m;
    struct timespec t_beg_q, t_end_q, t_beg_m, t_end_m;
    double rse_q, rse_m;

    size_t int_size = sizeof(int);
    size_t size;

    int counter_q = 20, counter_m = 20;

    srand(time(NULL));

    fq = fopen("tempq.txt", "a+t");
    fm = fopen("tempm.txt", "a+t");

    if (!fq || !fm)
    {
        return ERR_IO;
    }
        
    for (size_t i = 0; i < counter_q; i++)
    {   
        if (F == 0)
        {
            for (size_t j = 0; j < N; j++)
            {
                int s = rand();
                a[j] = s;
                b[j] = s;
            }
        }
        else
        {
            int s = rand();
            for (size_t j = 0; j < N; j++)
            {
                a[j] = j + s;
                b[j] = j + s;
            }
        }

        size = sizeof(a) / sizeof(a[0]);

        
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg_q);
        qsort(a, size, int_size, int_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end_q);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg_m);
        mysort(b, size, int_size, int_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end_m);
        

        sort_duration_q = time_calc(&t_beg_q, &t_end_q);
        sort_duration_m = time_calc(&t_beg_m, &t_end_m);

        fprintf(fq, "%llu ", sort_duration_q);
        fprintf(fm, "%llu ", sort_duration_m);

        rse_q = calc_rse(fq);
        rse_m = calc_rse(fm);
    }
    
    while (rse_q > RSE_IDEAL && rse_m > RSE_IDEAL)
    {
        counter_q++;
        counter_m++;
        
        if (F == 0)
        {
            for (size_t j = 0; j < N; j++)
            {
                int s = rand();
                a[j] = s;
                b[j] = s;
            }
        }
        else
        {
            int s = rand();
            for (size_t j = 0; j < N; j++)
            {
                a[j] = j + s;
                b[j] = j + s;
            }
        }

        size = sizeof(a) / sizeof(a[0]);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg_q);
        qsort(a, size, int_size, int_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end_q);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg_m);
        mysort(b, size, int_size, int_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end_m);
        

        sort_duration_q = time_calc(&t_beg_q, &t_end_q);
        sort_duration_m = time_calc(&t_beg_m, &t_end_m);


        fprintf(fq, "%llu ", sort_duration_q);
        fprintf(fm, "%llu ", sort_duration_m);

        rse_q = calc_rse(fq);
        rse_m = calc_rse(fm);
    }

    while (rse_q > RSE_IDEAL)
    {
        counter_q++;
        
        if (F == 0)
        {
            for (size_t j = 0; j < N; j++)
            {
                int s = rand();
                a[j] = s;
            }
        }
        else if (F == 1)
        {
            int s = rand();
            for (size_t j = 0; j < N; j++)
            {
                a[j] = j + s;
            }
        }


        size = sizeof(a) / sizeof(a[0]);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg_q);
        qsort(a, size, int_size, int_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end_q);
        
        sort_duration_q = time_calc(&t_beg_q, &t_end_q);

        fprintf(fq, "%llu ", sort_duration_q);

        rse_q = calc_rse(fq);
    }

    while (rse_m > RSE_IDEAL)
    {
        counter_m++;
        if (F == 0)
        {
            for (size_t j = 0; j < N; j++)
            {
                int s = rand();
                a[j] = s;
            }
        }
        else
        {
            int s = rand();
            for (size_t j = 0; j < N; j++)
            {
                a[j] = j + s;
            }
        }

        size = sizeof(a) / sizeof(a[0]);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg_m);
        mysort(a, size, int_size, int_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end_m);
        
        sort_duration_m = time_calc(&t_beg_m, &t_end_m);

        fprintf(fm, "%llu ", sort_duration_m);

        rse_m = calc_rse(fm);
    }

    double ans_q = calc_avg(fq);
    double ans_m = calc_avg(fm);
    printf("%d,%lf,%d,%lf,%lf,%d,%lf\n", N, ans_q, counter_q, rse_q, 
    ans_m, counter_m, rse_m);
    fclose(fq);
    fclose(fm);
    return ERR_OK;
}