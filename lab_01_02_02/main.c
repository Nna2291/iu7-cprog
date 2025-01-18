#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_EXIST 2


int main(void)
{
    double x0, y0, x1, y1, x2, y2;
    double side1, side2, side3, perimeter;

    printf("Enter coordinates of points: ");
    if (scanf("%lf %lf %lf %lf %lf %lf", &x0, &y0, &x1, &y1, &x2, &y2) != 6)
    {
        printf("Incorrect input\n");
        return ERR_IO;
    }

    side1 = sqrt(pow((x0 - x1), 2) + pow((y0 - y1), 2));
    side2 = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    side3 = sqrt(pow((x0 - x2), 2) + pow((y0 - y2), 2));

    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side3 + side2 <= side1)
    {
        printf("Triangle does not exist\n");
        return ERR_EXIST;
    }

    perimeter = side1 + side2 + side3;

    printf("Perimeter: %f\n", perimeter);
    return ERR_OK;
}
