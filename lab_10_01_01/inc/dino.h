#ifndef DINO_H__
#define DINO_H__

#include <stdio.h>

typedef struct 
{
    char *name;
    double weight;
    double height;
} dino_t;

dino_t *dino_read(FILE *f, int *rc);

void dino_free_content(dino_t *dino);

int print_dino(FILE *f, dino_t *dino);

int comparator(const void *dino1, const void *dino2);

#endif
