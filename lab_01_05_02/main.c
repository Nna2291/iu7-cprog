#include <stdio.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_OVERFLOW 2
#define ERR_RANGE 3

/*
 * @brief   Функция для вычисления числа фибоначии по номеру
 *
 * @param[in]   n   Номер числа фибоначчи
 * @param[in]   *fib    Указатель на переменную
 *
 * @return  Код ошибки
 */
int fibonachi_value(int n, unsigned int *fib)
{
    unsigned int fib0 = 0, fib1 = 1, c;
    if (n == 0)
    {
        c = fib0;
    }
    else if (n == 1)
    {
        c = fib1;
    }
    else
    {
        n += 1;
        for (int i = 2; i < n; i++)
        {
            c = fib0 + fib1;
            if (c < fib0)
            {
                return ERR_OVERFLOW;
            }
            fib0 = fib1;
            fib1 = c;
        }
    }
    *fib = c;
    return ERR_OK;
}

int main(void)
{
    int n;
    unsigned int fib;
    printf("input n: ");

    if (scanf("%d", &n) != 1)
    {
        printf("Incorrect input");
        return ERR_IO;
    }

    if (n < 0)
    {
        printf("Value must be greater or equals zero");
        return ERR_RANGE;
    }

    int rc = fibonachi_value(n, &fib);
    if (rc != ERR_OK)
    {
        printf("Int overflowed");
        return rc;
    }
    printf("%d", fib);
    return ERR_OK;
}
