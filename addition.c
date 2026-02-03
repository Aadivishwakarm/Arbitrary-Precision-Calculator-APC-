#include "operations.h"
#include "list.h"

void addition(node *h1, node *t1, node *h2, node *t2,
              node **h3, node **t3) 
{
    int carry = 0;

    while (t1 || t2 || carry) {
        int a = t1 ? t1->data : 0;
        int b = t2 ? t2->data : 0;
        int sum = a + b + carry;

        insert_at_first(h3, t3, sum % 10);
        carry = sum / 10;

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    trim_leading_zeros(h3, t3);
}
