#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50

//globaly decleration
char stack[N];
char infix[N],postfix[N];
int top = -1;

int push(char d)
{
    if(top == N-1)
        printf("overflow");
    else
        stack[++top] = d;
}

int pop()
{
    if(top == -1)
    {
        printf("underflow");
        return '\0';
    }
    else
        return stack[top--];
}

int isEmpty()
{
    return top == -1;
}

int precedence(char symbol)
{
    switch(symbol)
    {
    case'^':
        return(3);
    case'*':
    case'/':
        return(2);
    case'+':
    case'-':
        return(1);
    default:
        return(0);
    }
}

int IntoPostfix()
{
    int i,j=0;
    char symbol, next;
    for(i=0; i<strlen(infix); i++)
    {
        symbol = infix[i];

        switch(symbol)
        {
        case '(':
            push(symbol);
            break;
        case ')':
            while((next = pop())!='(')
                postfix[j++] = next;
            break;
        case'^':
        case'*':
        case'/':
        case'+':
        case'-':
            while(!isEmpty() && precedence(stack[top]) >= precedence(symbol))
                postfix[j++] = pop();
            push(symbol);
            break;
        default:
            postfix[j++] = symbol;
        }
    }
    while(!isEmpty())
    {
        postfix[j++] = pop();
        postfix[j] = '\0';
    }
}

int display()
{
    int i;
    printf("The postfix expression is : ");
    for(i=0; i<strlen(postfix); i++)
    {
        printf("%c",postfix[i]);
    }
}

int main()
{
    printf("Enter the expression :");
    scanf("%s",infix);

    IntoPostfix();
    display();
    return 0;
}
