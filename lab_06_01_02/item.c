#include <string.h>
#include <math.h>

#include "errors.h"
#include "item.h"

double calculate_density(const item_t *item)
{
    return item->weight / item->volume;
}

int item_read(FILE *f, item_t *item)
{
    char buf[TITLE_LEN_FOR_READ];
    double weight, volume;

    if (!fgets(buf, sizeof(buf), f))
    {
        return ERR_IO;
    }

    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n')
    {
        buf[len - 1] = 0;
        len--;
    }
    else
    {
        return ERR_OVERFLOW;
    }
    if (!len)
    {
        return ERR_DATA;
    }
    if (fscanf(f, "%lf", &weight) != 1)
    {
        return ERR_IO;
    }
    if (fscanf(f, "%lf", &volume) != 1)
    {
        return ERR_IO;
    }

    if (compare_double(volume, 0, EPSILON) || compare_double(weight, 0, EPSILON))
    {
        return ERR_DATA;
    }

    if (volume < 0 || weight < 0)
    {
        return ERR_DATA;
    }

    char tmp[2];
    fgets(tmp, sizeof(tmp), f);
    strcpy(item->title, buf);
    item->volume = volume;
    item->weight = weight;
    item->density = calculate_density(item);
    return ERR_OK;
}

void item_print(const item_t *item)
{
    printf("%s\n", item->title);
    printf("%lf\n", item->weight);
    printf("%lf", item->volume);
}

int item_cmp(const item_t *item1, const item_t *item2)
{
    if (item1->density > item2->density)
    {
        return 1;
    }
    else if (compare_double(item1->density, item2->density, EPSILON))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

bool item_substr(const item_t *item1, const char *substr)
{
    return strstr(item1->title, substr) != NULL;
}

bool compare_double(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}
