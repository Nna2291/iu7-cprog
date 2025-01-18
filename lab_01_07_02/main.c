#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define EPSILON_FOR_COMPARATION 1e-8

/*
 * @brief   Функция для сравнения двух вещественных чисел
 *
 * @param[in]   a   Первое сравнимое число
 * @param[in]   b   Второе сравнимое число
 * @param[in]   eps Точность сравнения
 *
 * @return  Равны ли числа или нет
 */
int compare_double(double a, double b, double eps)
{
    if (fabs(a - b) < eps)
    {
        return 1;
    }
    return 0;
}

/*
 * @brief   Реализация функции s(x), которая является рядом тейлора для функции f(x)
 *
 * @param[in]   x   аргумент функции
 * @param[in]   eps   точность
 * @param[out]  sum значение функции s(x)
 *
 * @return  значение функции s(x)
 */
double s(double x, double eps)
{
    double element = x * x * x / 6;
    double sum = x + element;
    int n = 3;
    double square_x = x * x;
    while (eps < fabs(element))
    {
        element *= (n * n * square_x) / ((n + 1) * (n + 2));
        sum += element;
        n += 2;
    }
    return sum;
}

int main(void)
{
    double x, epsilon;
    double delta_abs, delta_relative;

    printf("Enter x and eps: ");
    if (scanf("%lf%lf", &x, &epsilon) != 2)
    {
        printf("Error input");
        return ERR_IO;
    }
    if (fabs(x) > 1 || epsilon <= 0 || epsilon > 1)
    {
        printf("Range error");
        return ERR_RANGE;
    }

    double s_x = s(x, epsilon);
    double asin_x = asin(x);

    delta_abs = fabs(asin_x - s_x);

    if (compare_double(asin_x, 0, EPSILON_FOR_COMPARATION))
    {
        delta_relative = 0.0;
    }
    else
    {
        delta_relative = delta_abs / fabs(asin_x);
    }

    printf("%lf %lf %lf %lf", s_x, asin_x, delta_abs, delta_relative);
    return ERR_OK;
}

