#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define OPNDSIZE 10
#define MAXQUADS 20

// Quadruple structure
struct quadruple {
    char op;              // Operator: +, -, *, /, or =
    char op1[OPNDSIZE];   // First operand
    char op2[OPNDSIZE];   // Second operand
    char res[OPNDSIZE];   // Result variable
};

struct quadruple quads[MAXQUADS];
int numquads;

// Function to check if a string is an integer
int isint(char opnd[]) {
    for(int i=0; opnd[i] != '\0'; i++) {
        if(!isdigit(opnd[i]))
            return 0;
    }
    return 1;
}

// Calculate result of a quadruple with integer operands
int calculate(int i) {
    int res;
    switch(quads[i].op) {
        case '+': res = atoi(quads[i].op1) + atoi(quads[i].op2); break;
        case '-': res = atoi(quads[i].op1) - atoi(quads[i].op2); break;
        case '*': res = atoi(quads[i].op1) * atoi(quads[i].op2); break;
        case '/': res = atoi(quads[i].op1) / atoi(quads[i].op2); break;
        default: res = 0;
    }
    return res;
}

// Get constant value of an operand if it has been folded
char* getconstval(char opnd[]) {
    for(int i=0; i<numquads; i++) {
        if(quads[i].op == '=' && strcmp(quads[i].res, opnd) == 0)
            return quads[i].op1;
    }
    return opnd;
}

// Constant folding: evaluate operations with integer constants
void fold();

// Propagate constant values through quadruples
void propagate() {
    for(int i=0; i<numquads; i++) {
        strcpy(quads[i].op1, getconstval(quads[i].op1));
        strcpy(quads[i].op2, getconstval(quads[i].op2));
        if(isint(quads[i].op1) && isint(quads[i].op2)) {
            fold();
        }
    }
}

// Fold all constant expressions
void fold() {
    int changed = 0;
    for(int i=0; i<numquads; i++) {
        if(isint(quads[i].op1) && isint(quads[i].op2)) {
            int res = calculate(i);
            quads[i].op = '=';                // Replace operation with assignment
            sprintf(quads[i].op1, "%d", res); // Store computed constant
            strcpy(quads[i].op2, "-");        // Clear second operand
            changed = 1;
        }
    }
    if(changed) {
        propagate();
    }
}

// Main function
int main() {
    printf("How many quadruples? ");
    scanf("%d", &numquads);

    printf("Enter %d quadruples (format: op op1 op2 res)\n", numquads);
    printf("Example: + 2 3 t1  or = 5 - t1\n");

    for(int i=0; i<numquads; i++) {
        scanf(" %c %s %s %s", &quads[i].op, quads[i].op1, quads[i].op2, quads[i].res);
    }

    fold();

    printf("\nAfter CONSTANT FOLDING AND PROPAGATION\n");
    printf("Operator | Operand1 | Operand2 | Result\n");
    printf("======================================\n");
    for(int i=0; i<numquads; i++) {
        printf("%-8c | %-8s | %-8s | %s\n", quads[i].op, quads[i].op1, quads[i].op2, quads[i].res);
    }

    return 0;
}
