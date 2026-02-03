#include "operations.h"
#include "list.h"

void signed_addition(node *h1, node *t1, char sign1,
                     node *h2, node *t2, char sign2,
                     node **h3, node **t3) 
{
    if (sign1 == '+' && sign2 == '+') {
        addition(h1, t1, h2, t2, h3, t3);
        return;
    }

    if (sign1 == '-' && sign2 == '-') {
        addition(h1, t1, h2, t2, h3, t3);
        insert_at_first(h3, t3, -1);
        return;
    }

    if (sign1 == '+' && sign2 == '-') {
        if (compare_numbers(h1, h2) < 0) {
            subtraction(h2, t2, h1, t1, h3, t3);
            insert_at_first(h3, t3, -1);
        } else {
            subtraction(h1, t1, h2, t2, h3, t3);
        }
        return;
    }

    if (sign1 == '-' && sign2 == '+') {
        if (compare_numbers(h2, h1) < 0) {
            subtraction(h1, t1, h2, t2, h3, t3);
            insert_at_first(h3, t3, -1);
        } else {
            subtraction(h2, t2, h1, t1, h3, t3);
        }
        return;
    }
}
