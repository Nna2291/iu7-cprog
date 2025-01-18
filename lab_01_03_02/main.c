#include <stdio.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int main(void)
{
    float r1, r2, r3;
    float r;

    printf("Enter reistance of three resistors: ");

    if (scanf("%f%f%f", &r1, &r2, &r3) != 3)
    {
        printf("Incorrect input\n");
        return ERR_IO;
    }

    if (r1 <= 0 || r2 <= 0 || r3 <= 0)
    {
        printf("Resistance must be greater than zero\n");
        return ERR_RANGE;
    }

    r = 1 / (1 / r1 + 1 / r2 + 1 / r3);

    printf("%f", r);
    return ERR_OK;
}
