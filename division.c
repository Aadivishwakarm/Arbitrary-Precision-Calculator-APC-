#include <stdlib.h>
#include "operations.h"
#include "list.h"

/* Helper: append a digit at end (used for remainder building) */
static void append_digit(node **h, node **t, int d)
{
    insert_at_end(h, t, d);
}

/* Helper: multiply a number (h..t) by a single digit (0-9),
 * store result in rh..rt as a new list.
 * Operates on non-negative magnitudes only.
 */
static void multiply_single(node *h, node *t, int digit,
                            node **rh, node **rt)
{
    int carry = 0;
    while (t || carry) {
        int v = (t ? t->data : 0) * digit + carry;
        insert_at_first(rh, rt, v % 10);
        carry = v / 10;
        if (t) t = t->prev;
    }
    trim_leading_zeros(rh, rt);
}

/* Helper: remainder = remainder - value (both non-negative, remainder>=value) */
static void subtract_lists_into(node **h, node **t,
                                node *h2, node *t2)
{
    node *r = NULL, *rt = NULL;
    subtraction(*h, *t, h2, t2, &r, &rt);

    free_list(h, t);
    *h = r;
    *t = rt;
}

/* Long division on magnitudes: (h1..t1) / (h2..t2) -> quotient in qh..qt
 * Both inputs are non-negative, no sign nodes.  Result is non-negative.
 */
void division(node *h1, node *t1, node *h2, node *t2,
              node **qh, node **qt)
{
    /* divide by zero -> return 0 (you can change this to an error handling) */
    if (!h2 || (h2->data == 0 && h2->next == NULL)) {
        insert_at_end(qh, qt, 0);
        return;
    }

    /* If dividend is 0 -> quotient is 0 */
    if (!h1 || (h1->data == 0 && h1->next == NULL)) {
        insert_at_end(qh, qt, 0);
        return;
    }

    node *rh = NULL, *rt = NULL;   /* remainder */
    node *p = h1;                  /* iterate through dividend digits */

    while (p) {
        /* Bring down next digit into remainder */
        append_digit(&rh, &rt, p->data);
        trim_leading_zeros(&rh, &rt);

        /* Find largest digit q in [0..9] such that divisor*q <= remainder */
        int qdigit = 0;

        for (int d = 0; d <= 9; d++) {
            node *mh = NULL, *mt = NULL;
            multiply_single(h2, t2, d, &mh, &mt);

            if (compare_numbers(mh, rh) <= 0)
                qdigit = d;

            free_list(&mh, &mt);
        }

        /* Append quotient digit */
        insert_at_end(qh, qt, qdigit);

        /* remainder -= divisor * qdigit */
        node *mh = NULL, *mt = NULL;
        multiply_single(h2, t2, qdigit, &mh, &mt);
        subtract_lists_into(&rh, &rt, mh, mt);
        free_list(&mh, &mt);

        p = p->next;
    }

    trim_leading_zeros(qh, qt);

    /* Safety: if somehow quotient is empty, make it 0 */
    if (!*qh) {
        insert_at_end(qh, qt, 0);
    }

    free_list(&rh, &rt);
}
