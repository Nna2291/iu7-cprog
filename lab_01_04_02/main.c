#include <stdio.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60

int main(void)
{
    int time;
    int hour, minute, second;

    printf("Enter time: ");
    if (scanf("%d", &time) != 1)
    {
        printf("Incorrect input\n");
        return ERR_IO;
    }

    if (time < 0)
    {
        printf("Value must be greater or equals zero\n");
        return ERR_RANGE;
    }

    hour = time / SECONDS_IN_HOUR;
    time %= SECONDS_IN_HOUR;
    minute = time / SECONDS_IN_MINUTE;
    time %= SECONDS_IN_MINUTE;
    second = time;

    printf("Hours: %d Minutes: %d Seconds: %d", hour, minute, second);
    return ERR_OK;
}
