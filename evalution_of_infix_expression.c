#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 50

int val_stack[MAX_SIZE];
int val_top = -1;

char op_stack[MAX_SIZE];
int op_top = -1;

void push_val(int item)
{
    if(val_top == MAX_SIZE-1)
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    val_stack[++val_top] = item;
}

int pop_val()
{
    if(val_top == -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    return val_stack[val_top--];
}

void push_op(char item)
{
    if(op_top == MAX_SIZE-1)
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    op_stack[++op_top] = item;
}

char pop_op()
{
    if(op_top == -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    return op_stack[op_top--];
}

int precedence(char op)
{
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

void eval_step()
{
    int op2 = pop_val();
    int op1 = pop_val();
    char op = pop_op();
    int result;
    
    switch(op)
    {
    case '+': result = op1 + op2; break;
    case '-': result = op1 - op2; break;
    case '*': result = op1 * op2; break;
    case '/': result = op1 / op2; break;
    default:
        printf("Invalid operator\n");
        exit(1);
    }
    push_val(result);
}

int evaluate(char infix[])
{
    int i;
    for(i=0; infix[i]!='\0'; i++)
    {
        if(infix[i] >= '0' && infix[i] <= '9')
        {
            push_val(infix[i] - '0');
        }
        else if(infix[i] == '(')
        {
            push_op(infix[i]);
        }
        else if(infix[i] == ')')
        {
            while(op_top != -1 && op_stack[op_top] != '(')
            {
                eval_step();
            }
            pop_op();
        }
        else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
        {
            while(op_top != -1 && precedence(op_stack[op_top]) >= precedence(infix[i]))
            {
                eval_step();
            }
            push_op(infix[i]);
        }
    }
    
    while(op_top != -1)
    {
        eval_step();
    }
    
    return pop_val();
}

int main()
{
    char infix[50];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    int result = evaluate(infix);
    printf("Result: %d\n", result);
    return 0;
}
