#include "operations.h"
#include "list.h"

void insert_number(node **head, node **tail, char *str) 
{
    for (int i = 0; str[i]; i++) {
        /* assume str[i] is a digit */
        insert_at_end(head, tail, str[i] - '0');
    }
}
