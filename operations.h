#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "list.h"

/* Convert a numeric string (no sign) to list */
void insert_number(node **head, node **tail, char *str);

/* Basic arithmetic on positive magnitudes (no sign nodes). */
void addition(node *h1, node *t1, node *h2, node *t2,
              node **h3, node **t3);
void subtraction(node *h1, node *t1, node *h2, node *t2,
                 node **h3, node **t3);
void multiplication(node *h1, node *t1, node *h2, node *t2,
                    node **h3, node **t3);
void division(node *h1, node *t1, node *h2, node *t2,
              node **h3, node **t3);

/* Compare two non-negative numbers (no sign nodes).
 * Returns >0 if h1>h2, <0 if h1<h2, 0 if equal.
 */
int compare_numbers(node *h1, node *h2);

/* Handles sign logic for addition:
 * sign1, sign2 are '+' or '-'.
 * Result sign is encoded as a node with data = -1 at the head
 * (if result is negative).
 */
void signed_addition(node *h1, node *t1, char sign1,
                     node *h2, node *t2, char sign2,
                     node **h3, node **t3);

#endif
