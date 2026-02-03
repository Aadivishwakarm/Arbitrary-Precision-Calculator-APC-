#include "operations.h"

int compare_numbers(node *h1, node *h2) 
{
    int len1 = 0, len2 = 0;
    for (node *p = h1; p; p = p->next) len1++;
    for (node *p = h2; p; p = p->next) len2++;

    if (len1 != len2) return len1 - len2;

    node *p1 = h1, *p2 = h2;
    while (p1 && p2) {
        if (p1->data != p2->data)
            return p1->data - p2->data;
        p1 = p1->next;
        p2 = p2->next;
    }
    return 0;
}
