#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_EXIST 2

#define POINT_INSIDE 0
#define POINT_ON_SIDE 1
#define POINT_OUTSIDE 2

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
 * @brief   Функция для проверки существует ли треугольник
 *
 * @param[in]   a   сторона треугольника
 * @param[in]   b   сторона треугольника
 * @param[in]   c   сторона треугольника
 *
 * @return  Существует ли треугольник или нет
 */
int triangle_rule(double a, double b, double c)
{
    if (a + b <= c || a + c <= b || c + b <= a)
    {
        return 0;
    }
    return 1;
}

/*
 * @brief   Функция для расчета длины вектора с помощью координат
 *
 * @param[in]   x0    координата x вектора 1
 * @param[in]   y0    координата y вектора 1
 * @param[in]   x1    координата x вектора 2
 * @param[in]   y1    координата y вектора 2
 *
 * @return  Длина вектора
 */
double calc_size(double x0, double y0, double x1, double y1)
{
    return sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
}

/*
 * @brief   Функция для расчета скалярного произведения векторов
 *
 * @param[in]   x1    координата x вектора 1
 * @param[in]   x0    координата x вектора 0
 * @param[in]   y2    координата y вектора 2
 * @param[in]   y1    координата y вектора 1
 * @param[in]   x2    координата x вектора 2
 * @param[in]   y0    координата y вектора 0
 *
 * @return  Скалярное произведение
 */
double scalar_calc(double x1, double x0, double y2, double y1, double x2, double y0)
{
    return (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
}

/*
 * @brief   Функция для расчета положения точки относительно треугольника
 *
 * @param[in]   scalar1 Скалярное произведние с первой стороной
 * @param[in]   scalar2 Скалярное произведние со второй стороной
 * @param[in]   scalar3 Скалярное произведние с третьей стороной
 *
 * @return  Положение точки относительно треугольника (на стороне, снаружи треугольника, внутри треугольника)
 */
int calculate_answer(double scalar1, double scalar2, double scalar3, double epsilon)
{
    if (compare_double(scalar1, 0, epsilon) || compare_double(scalar2, 0, epsilon) ||
        compare_double(scalar3, 0, epsilon))
    {
        return POINT_ON_SIDE;
    }
    else if (scalar1 > 0 && scalar2 > 0 && scalar3 > 0)
    {
        return POINT_INSIDE;
    }
    else if (scalar1 < 0 && scalar2 < 0 && scalar3 < 0)
    {
        return POINT_INSIDE;
    }
    else
    {
        return POINT_OUTSIDE;
    }
}

int main(void)
{
    double xp, yp, x1, y1, x2, y2, x3, y3;
    double scalar1, scalar2, scalar3;
    double side1, side2, side3;
    double epsilon = 1e-8;

    int answer;

    printf("Enter coordinates of triangle points: ");
    if (scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) != 6)
    {
        printf("Incorrect input\n");
        return ERR_IO;
    }

    printf("Enter coordinates of point: ");

    if (scanf("%lf %lf", &xp, &yp) != 2)
    {
        printf("Incorrect input\n");
        return ERR_IO;
    }

    side1 = calc_size(x1, y1, x2, y2);
    side2 = calc_size(x2, y2, x3, y3);
    side3 = calc_size(x1, y1, x3, y3);

    if (!triangle_rule(side1, side2, side3))
    {
        printf("Triangle does not exist\n");
        return ERR_EXIST;
    }

    scalar1 = scalar_calc(x1, xp, y2, y1, x2, yp);
    scalar2 = scalar_calc(x2, xp, y3, y2, x3, yp);
    scalar3 = scalar_calc(x3, xp, y1, y3, x1, yp);
    answer = calculate_answer(scalar1, scalar2, scalar3, epsilon);
    printf("%d", answer);

    return ERR_OK;
}
