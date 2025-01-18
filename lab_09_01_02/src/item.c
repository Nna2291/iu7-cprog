#define _GNU_SOURCE

#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "utils.h"
#include "item.h"

double calculate_density(double weight, double volume)
{
    return weight / volume;
}

int item_init(item_t *pitem, const char *title, double weight, double volume, double density)
{
    char *tmp = strdup(title);
    if (!tmp)
    {
        return ERR_MEMORY;
    }

    item_free_content(pitem);
    pitem->title = tmp;
    pitem->weight = weight;
    pitem->volume = volume;
    pitem->density = density;
        
    return ERR_OK;
}


int item_copy(item_t *pdst, const item_t *psrc)
{
    int rc = ERR_OK;
    rc = item_init(pdst, psrc->title, psrc->weight, psrc->volume, psrc->density);
    return rc;
}

void item_free_content(item_t *pitem)
{
    free(pitem->title);
    pitem->title = NULL;
}

int item_read(FILE *f, item_t *pitem)
{
    char *buf = NULL;
    size_t len = 0;
    size_t read;
    double weight = 0.0, volume = 0.0;
    int rc = ERR_IO;
    if ((read = getline(&buf, &len, f)) == -1)
    {
        free(buf);
        return rc;
    }
   
    char *p = strrchr(buf, '\n');
    if (p)
    {
        *p = 0;
        read -= 1;
    }
    
    if (read)
    {
        if (fscanf(f, "%lf %lf\n", &weight, &volume) != 2)
        {
            rc = ERR_IO;
        }

        if (compare_double(weight, 0.0, EPSILON) == 0 || 
            compare_double(volume, 0.0, EPSILON) == 0 || 
            compare_double(weight, 0.0, EPSILON) < 0 || 
            compare_double(volume, 0.0, EPSILON) < 0)
        {
            rc = ERR_DATA;
        }
        else
        {
            rc = item_init(pitem, buf, weight, volume, calculate_density(weight, volume));
        }   
    }
    else
    {
        rc = ERR_DATA;
    }
    free(buf);
    return rc;
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
    return (strncmp(substr, (*item1).title, strlen(substr)) == 0);
}
