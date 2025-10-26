#include <stdio.h>
#include <string.h>
#define SIZE 50
#define MAXPROD 20
#define NUMPROD 5

char input[SIZE], stack[SIZE];
int ip_ptr = 0, top = -1;

char productions[NUMPROD][MAXPROD] = {"E=E+T", "E=T", "T=T*F", "T=F", "F=i"};

void shift(char c)
{
    stack[++top] = c;
    stack[top + 1] = '\0';
    printf("%-10s\t%-10s\tShift %c\n", stack, input + ip_ptr, c);
}

void reduce(int prod_no)
{
    char *rhs = productions[prod_no] + 2;
    int len = strlen(rhs);

    // check if RHS exists at top
    if (top + 1 >= len && strcmp(stack + top - len + 1, rhs) == 0)
    {
        top = top - len + 1;
        stack[top] = productions[prod_no][0]; // replace RHS with LHS
        stack[top + 1] = '\0';

        printf("%-10s\t%-10s\tReduced by %s\n", stack, input + ip_ptr, productions[prod_no]);
    }
}

int main()
{
    printf("Enter the string: ");
    scanf("%s", input);

    printf("\nSHIFT-REDUCE PARSING\n");
    printf("Stack\t\tInput\t\tAction\n");
    printf("-----\t\t-----\t\t------\n");

    while (input[ip_ptr] != '\0')
    {
        shift(input[ip_ptr++]);

        int reduced = 1;
        while (reduced)
        {
            reduced = 0;
            for (int i = 0; i < NUMPROD; i++)
            {
                char *pos = strstr(stack, productions[i] + 2);
                if (pos != NULL)
                {
                    reduce(i);
                    reduced = 1;
                    break; // check again from start after a reduction
                }
            }
        }
    }

    if (top == 0 && stack[top] == 'E')
        printf("\nInput Accepted ✅\n");
    else
        printf("\nInput Rejected ❌\n");

    return 0;
}
