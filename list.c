#include <stdlib.h>
#include "list.h"

void insert_at_end(node **head, node **tail, int val) {
    node *new = (node *)malloc(sizeof(node));
    if (!new) return; /* allocation failure: in real code handle error */
    new->data = val;
    new->next = NULL;
    new->prev = *tail;

    if (*tail)
        (*tail)->next = new;
    else
        *head = new;

    *tail = new;
}

void insert_at_first(node **head, node **tail, int val) {
    node *new = (node *)malloc(sizeof(node));
    if (!new) return; /* allocation failure */
    new->data = val;
    new->prev = NULL;
    new->next = *head;

    if (*head)
        (*head)->prev = new;
    else
        *tail = new;

    *head = new;
}

void free_list(node **head, node **tail) {
    node *cur = *head;
    while (cur) {
        node *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
    *tail = NULL;
}

void trim_leading_zeros(node **head, node **tail) {
    if (!head || !*head) return;

    node *p = *head;

    /* Remove leading zeros but leave one node if all zeros */
    while (p && p->data == 0 && p->next) {
        node *tmp = p;
        p = p->next;
        p->prev = NULL;
        free(tmp);
    }

    *head = p;

    if (!p) {
        *tail = NULL;
        return;
    }

    node *q = p;
    while (q->next) q = q->next;
    *tail = q;
}
