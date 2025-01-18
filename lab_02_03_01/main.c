#include <stdio.h>
#include <stdbool.h>

#define N 20
#define N_INPUT (N / 2)
#define DIVIDER 3

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int fibonachi_value(int n)
{
    unsigned int fib0 = 0, fib1 = 1, num;
    if (n == 0)
    {
        num = fib0;
    }
    else if (n == 1)
    {
        num = fib1;
    }
    else
    {
        n += 1;
        for (int i = 2; i < n; i++)
        {
            num = fib0 + fib1;
            fib0 = fib1;
            fib1 = num;
        }
    }
    return num;
}

int input(int array[], size_t *n)
{
    printf("Input n: ");
    if (scanf("%zu", n) != 1)
        return ERR_IO;

    if (*n > N_INPUT || *n == 0)
        return ERR_RANGE;

    printf("Input integers of array: \n");
    for (size_t i = 0; i < *n; i++)
    {
        if (scanf("%d", &array[i]) != 1)
            return ERR_IO;
    }

    return ERR_OK;
}

void input_element(int array[], size_t *size, size_t index, int element)
{
    for (size_t i = (*size) - 1; i >= index; i--)
    {
        array[i + 1] = array[i];
    }
    array[index] = element;
    (*size)++;
}

bool is_divided_by_number(int number, int divider)
{
    return number % divider == 0;
}

void fill_array(int array[], size_t *size)
{
    unsigned int n = 0;
    size_t i = 0;
    while (i < *size)
    {
        if (is_divided_by_number(array[i], DIVIDER))
        {
            int fib = fibonachi_value(n);
            input_element(array, size, i + 1, fib);
            n++;
            i++;
        }
        i++;
    }
}

void print_array(const int array[], size_t size)
{
    printf("Array elements: ");
    for (size_t i = 0; i < size - 1; i++)
    {
        printf("%d ", array[i]);
    }
    printf("%d\n", array[size - 1]);
}

int main(void)
{
    int array[N];
    size_t size;

    int rc = input(array, &size);
    if (rc != ERR_OK)
    {
        return rc;
    }

    fill_array(array, &size);
    print_array(array, size);
    
    return ERR_OK;
}
