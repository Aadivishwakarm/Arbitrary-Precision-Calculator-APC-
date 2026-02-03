#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "list.h"

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s <num1> <op> <num2>\n", argv[0]);
        printf("Example: %s 123 + 456\n", argv[0]);
        return 1;
    }

    char *a = argv[1];
    char *op = argv[2];
    char *b = argv[3];

    char sign1 = (a[0] == '-') ? '-' : '+';
    char sign2 = (b[0] == '-') ? '-' : '+';

    node *h1 = NULL, *t1 = NULL;
    node *h2 = NULL, *t2 = NULL;
    node *h3 = NULL, *t3 = NULL;

    /* Load the magnitudes only */
    insert_number(&h1, &t1, (a[0]=='-') ? a+1 : a);
    insert_number(&h2, &t2, (b[0]=='-') ? b+1 : b);

    /* ===========================
           SWITCH-CASE LOGIC
       =========================== */

    switch (op[0])
    {
        case '+':
            printf("===========================\n");
            printf("    Addition selected.\n");
            printf("===========================\n");
            signed_addition(h1, t1, sign1, h2, t2, sign2, &h3, &t3);
            break;

        case '-': 
        {
            printf("===========================\n");
            printf("    Substraction selected.\n");
            printf("===========================\n");
            char sign2_for_sub = (sign2 == '+') ? '-' : '+';
            signed_addition(h1, t1, sign1, h2, t2, sign2_for_sub, &h3, &t3);
            break;
        }

        case 'x':
        {        
            printf("===========================\n");
            printf("  Multiplication selected.\n");
            printf("===========================\n");
            multiplication(h1, t1, h2, t2, &h3, &t3);
            
            int zero = (h3->data == 0 && h3->next == NULL);
            if ((sign1 != sign2) && !zero)
                insert_at_first(&h3, &t3, -1);
            break;
        }

        case '/': 
        {
            printf("===========================\n");
            printf("    Division selected.\n");
            printf("===========================\n");
            division(h1, t1, h2, t2, &h3, &t3);

            int zero = (h3->data == 0 && h3->next == NULL);
            if ((sign1 != sign2) && !zero)
                insert_at_first(&h3, &t3, -1);
            break;
        }

        default:
            printf("Invalid operator '%s'. Use +  -  x  *  /\n", op);
            free_list(&h1, &t1);
            free_list(&h2, &t2);
            return 1;
    }

    /* ===========================
           PRINT RESULT
       =========================== */

    if (!h3) {
        printf("Error: result empty.\n");
        return 1;
    }

    node *p = h3;

    if (p->data == -1) {
        printf("-");
        p = p->next;
    }

    while (p) {
        printf("%d", p->data);
        p = p->next;
    }

    printf("\n");

    free_list(&h1, &t1);
    free_list(&h2, &t2);
    free_list(&h3, &t3);

    return 0;
}
