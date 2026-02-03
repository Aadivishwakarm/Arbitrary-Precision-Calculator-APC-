#ifndef LIST_H
#define LIST_H

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node;

void insert_at_end(node **head, node **tail, int val);
void insert_at_first(node **head, node **tail, int val);
void free_list(node **head, node **tail);

/* Remove leading zeros from a non-negative digit list.
 * Leaves a single 0 node if the number is zero.
 */
void trim_leading_zeros(node **head, node **tail);

#endif
