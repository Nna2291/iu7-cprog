#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/*
 * @brief Выделим повторяющееся выражение в функции
 *
 * @param[in]   n   Номер n
 * @param[in]   x   Аргумент функции
 *
 * @return  Значение выражения
*/
double custom_sqrt(int n, double x)
{
    return sqrt(n + x);
}

/*
 * @brief  Функция для считывания чисел в последовательность
 *
 * @param[in]   *x   Указатель на аргумент функции
 * @param[in]   *n   Указатель на номер n
 * @param[in]   *answer   Указатель на значение функции g(x)
 *
 * @return  Код ошибки
 */
int read_numbers(double *x, int *n, double *answer)
{
    do
    {
        *n += 1;
        *answer += custom_sqrt(*n, *x);
        if (scanf("%lf", x) != 1)
        {
            return ERR_IO;
        }
    } while (*x >= 0);
    if (*n == 0)
    {
        return ERR_RANGE;
    }
    *answer /= *n;
    return ERR_OK;
}

int main(void)
{
    int n = -1;
    double x = 0;
    double answer = 0;
    printf("Enter number: ");
    int rc = read_numbers(&x, &n, &answer);
    if (rc == ERR_IO)
    {
        printf("Error input!");
        return rc;
    } 
    else if (rc == ERR_RANGE)
    {
        printf("Sequence cant be empty!");
        return rc;
    }
    
    printf("%lf", answer);
    return rc;
}
