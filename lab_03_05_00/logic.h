#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

void put_back_in_matrix(const int array[], int matrix[][M], size_t n, size_t m);

void reverse_array(int arr[], int k);

int put_primes(int array[], const int matrix[][M], size_t n, size_t m);

#endif
