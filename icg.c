#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 50
#define VARLEN 10

char opstack[MAXSIZE];             // operator stack
char opndstack[MAXSIZE][VARLEN];   // operand stack
int opstktop = -1, opndstktop = -1;
char expn[MAXSIZE * 5];            // input expression
int tempcount = 1;

// function prototypes
int priority(char c);
void push_op(char c);
char pop_op();
void push_opnd(char *str);
void pop_opnd(char *str);
void generate(char op);
void icg_from_infix();

// get operator priority
int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '=') return -1;
    return 0;
}

// push operator
void push_op(char c) {
    opstack[++opstktop] = c;
}

// pop operator
char pop_op() {
    return opstack[opstktop--];
}

// push operand
void push_opnd(char *str) {
    strcpy(opndstack[++opndstktop], str);
}

// pop operand
void pop_opnd(char *str) {
    strcpy(str, opndstack[opndstktop--]);
}

// generate 3-address code for one operation
void generate(char op) {
    char op2[VARLEN], op1[VARLEN], temp[VARLEN];
    pop_opnd(op2);
    pop_opnd(op1);
    sprintf(temp, "t%d", tempcount++);
    printf("%s = %s %c %s\n", temp, op1, op, op2);
    push_opnd(temp); // push result back as operand
}

// main ICG function
void icg_from_infix() {
    int i = 0;
    char temp[VARLEN];

    printf("Enter infix expression: ");
    scanf("%s", expn);

    while (expn[i] != '\0') {
        if (isalnum(expn[i])) { // if operand (a,b,c,1,2,...)
            int j = 0;
            while (isalnum(expn[i])) {
                temp[j++] = expn[i++];
            }
            temp[j] = '\0';
            push_opnd(temp);
        } 
        else if (expn[i] == '(') {
            push_op(expn[i]);
            i++;
        } 
        else if (expn[i] == ')') {
            while (opstack[opstktop] != '(') {
                char op = pop_op();
                generate(op);
            }
            opstktop--; // pop '('
            i++;
        } 
        else { // operator +, -, *, /
            while (opstktop != -1 && priority(opstack[opstktop]) >= priority(expn[i])) {
                char op = pop_op();
                generate(op);
            }
            push_op(expn[i]);
            i++;
        }
    }

    // handle remaining operators
    while (opstktop != -1) {
        char op = pop_op();
        generate(op);
    }
}

// driver code
int main() {
    icg_from_infix();
    return 0;
}
