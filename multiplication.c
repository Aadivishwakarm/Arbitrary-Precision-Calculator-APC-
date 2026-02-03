#include <stdlib.h>
#include "operations.h"
#include "list.h"

void multiplication(node *h1, node *t1, node *h2, node *t2,
                    node **h3, node **t3) 
{
    int len1 = 0, len2 = 0;
    for (node *p = h1; p; p = p->next) len1++;
    for (node *p = h2; p; p = p->next) len2++;

    int *res = (int *)calloc(len1 + len2, sizeof(int));
    if (!res) return;

    int i = 0;
    for (node *p1 = t1; p1; p1 = p1->prev, i++) {
        int j = 0;
        for (node *p2 = t2; p2; p2 = p2->prev, j++) {
            res[i + j] += p1->data * p2->data;
        }
    }

    int carry = 0;
    for (int k = 0; k < len1 + len2; k++) {
        int tmp = res[k] + carry;
        res[k] = tmp % 10;
        carry = tmp / 10;
    }

    int k = len1 + len2 - 1;
    while (k > 0 && res[k] == 0) k--;

    for (; k >= 0; k--) {
        insert_at_end(h3, t3, res[k]);
    }

    free(res);

    trim_leading_zeros(h3, t3);
}
