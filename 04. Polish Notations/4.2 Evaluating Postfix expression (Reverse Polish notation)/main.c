/*
 * File:   Evaluating Postfix expression (Reverse Polish notation)
 * Author: Pranshu Shelat
 *
 * Created on: October 13, 2017
 *
 * Details: This program accepts a postfix notation and evaluates it.
            It uses stack for processing the operands.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

typedef struct {
  double item[SIZE];
  int top;
} OperandStack;

// function prototypes

// stack funtions
void push(OperandStack *, double);
double pop(OperandStack *);
int isEmpty(OperandStack *);

// postfix notation functions
double operate(double, double, char);
double evalPostfix(char *);

// Push Operation
void push(OperandStack *sp, double val){
  // checking overflow
  if(sp->top == SIZE-1){
    printf("Stack Overflow, terminating program...\n");
    exit(1);
  }
  // otherwise, push
  sp->top++;
  sp->item[sp->top] = val;
}

// Pop Operation
double pop(OperandStack *sp){
  // checking underflow
  if(isEmpty(sp)){
    printf("Stack Underflow, terminating program...\n");
    exit(1);
  }
  // otherwise, pop
  double val = sp->item[sp->top];
  sp->top--;
  return val;
}

// If stack is empty return 1, otherwise 0
int isEmpty(OperandStack *sp){
  // checking underflow
  return sp->top == -1;
}

// Operation function
double operate(double leftOpnd, double rightOpnd, char opr){
  switch(opr){
    case '+': return leftOpnd + rightOpnd; printf("%lf\n", leftOpnd + rightOpnd); break;
    case '-': return leftOpnd - rightOpnd; break;
    case '*': return leftOpnd * rightOpnd; break;
    case '/': return leftOpnd / rightOpnd; break;
    case '$': return pow(leftOpnd,rightOpnd); break;
    default: printf("%c is not a valid operator\n", opr); exit (1);
  }
}

double evalPostfix(char postfix[]){
  OperandStack stack;
  stack.top = -1;
  int i = 0;
  while(postfix[i] != '\0'){
    char token = postfix[i];
    if(token >= '0' && token <='9'){
      int v = token - '0';
      push(&stack, (double)v);
    }
    else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '$'){
      double opnd1 = pop(&stack);
      double opnd2 = pop(&stack);
      double result = operate(opnd2, opnd1, token);
      push(&stack, result);
    }
    else{
      printf("Invalid character encountered, terminating program...\n");
      exit(1);
    }
    i++;
  }
  return pop(&stack);
}

int main() {
  char postfix[SIZE];
  printf("Enter the postfix expression: ");
  scanf("%s", postfix);
  double result = evalPostfix(postfix);
  printf("Result: %lf\n", result);
  return 0;
}
