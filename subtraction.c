#include "operations.h"
#include "list.h"

void subtraction(node *h1, node *t1, node *h2, node *t2,
                 node **h3, node **t3) 
{
    /* Ensure h1 >= h2 (by value) so result is non-negative */
    if (compare_numbers(h2, h1) > 0) {
        node *th = h1;
        h1 = h2;
        h2 = th;
        node *tt = t1; 
        t1 = t2; 
        t2 = tt;
    }

    int borrow = 0;
    while (t1 || t2) {
        int a = t1 ? t1->data : 0;
        int b = t2 ? t2->data : 0;

        a -= borrow;

        if (a < b) {
            a += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insert_at_first(h3, t3, a - b);

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    trim_leading_zeros(h3, t3);
}
