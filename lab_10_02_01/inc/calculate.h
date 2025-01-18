#ifndef CALCULATE_H__
#define CALCULATE_H__

#include "node.h"

int calculate_val(const node_t *head, int a, int *val);

int calculate_derivative(const node_t *head, node_t **new_head);

int calculate_sum(const node_t *head1, const node_t *head2, node_t **head3);

int divide_poly(const node_t *head, node_t **head_odd, node_t **head_even);

#endif
