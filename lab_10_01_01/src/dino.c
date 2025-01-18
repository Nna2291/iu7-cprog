#define _GNU_SOURCE
#define EPSILON 1e-9

#include <stdlib.h>
#include <string.h>

#include "dino.h"
#include "errors.h"
#include "utils.h"

dino_t *dino_read(FILE *f, int *rc)
{
    char *buf = NULL;
    size_t len = 0;
    size_t read;
    double weight = 0.0;
    double height = 0.0;
    dino_t *dino_tmp = malloc(sizeof(dino_t));
    if ((read = getline(&buf, &len, f)) == -1)
    {
        free(dino_tmp);
        free(buf);
        *rc = ERR_DATA;
        return NULL;
    }
   
    char *p = strrchr(buf, '\n');
    if (p)
    {
        *p = 0;
        read -= 1;
    }
    
    if (read)
    {
        if (fscanf(f, "%lf %lf\n", &weight, &height) != 2)
        {
            free(dino_tmp);
            free(buf);
            *rc = ERR_DATA;
            return NULL;
        }

        if (compare_double(weight, 0.0, EPSILON) == 0 ||
            compare_double(weight, 0.0, EPSILON) < 0 || 
            compare_double(height, 0.0, EPSILON) == 0 ||
            compare_double(height, 0.0, EPSILON) < 0)
        {
            free(dino_tmp);
            free(buf);
            *rc = ERR_DATA;
            return NULL;
        }
        else
        {
            char *tmp = strdup(buf);
            dino_tmp->weight = weight;
            dino_tmp->height = height;
            dino_tmp->name = tmp;
        }   
    }
    else
    {
        free(dino_tmp);
        free(buf);
        *rc = ERR_DATA;
        return NULL;
    }
    free(buf);
    *rc = ERR_OK;
    return dino_tmp;
}

int print_dino(FILE *f, dino_t *dino)
{
    if (fprintf(f, "%s %lf %lf\n", dino->name, dino->weight, dino->height) < 0)
    {
        return ERR_IO;
    }
    return ERR_OK;
}

void dino_free_content(dino_t *dino)
{
    if (!dino)
    {
        return;
    }
    free(dino->name);
}

int comparator(const void *dino1, const void *dino2)
{
    return compare_double(((dino_t*) dino1)->weight, ((dino_t*) dino2)->weight, EPSILON);
}
