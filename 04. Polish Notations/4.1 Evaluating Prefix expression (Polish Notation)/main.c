/*
 * File:   Evaluating prefix expression (Reverse Polish notation)
 * Author: Pranshu Shelat
 *
 * Created on: October 13, 2017
 *
 * Details: This program accepts a prefix notation and evaluates it.
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

typedef struct {
  char item[SIZE];
  int top;
} ExpressionStack;

// function prototypes

// operand stack funtions
void push(OperandStack *, double);
double pop(OperandStack *);
int isEmpty(OperandStack *);

// expression stack funtions
void pushc(ExpressionStack *, char);
char popc(ExpressionStack *);
int isEmptyc(ExpressionStack *);

// prefix notation functions
double operate(double, double, char);
double evalPrefix(char *);

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

void pushc(ExpressionStack *sp, char c){
  // checking overflow
  if(sp->top == SIZE-1){
    printf("Stack Overflow, terminating program...\n");
    exit(1);
  }/
  // otherwise, push
  sp->top++;
  sp->item[sp->top] = c;
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

char popc(ExpressionStack *sp){
  // checking underflow
  if(isEmptyc(sp)){
    printf("Stack Underflow, terminating program...\n");
    exit(1);
  }
  // otherwise, pop
  char c = sp->item[sp->top];
  sp->top--;
  return c;
}

// If stack is empty return 1, otherwise 0
int isEmpty(OperandStack *sp){
  // checking underflow
  return sp->top == -1;
}

int isEmptyc(ExpressionStack *sp){
  // checking underflow
  return sp->top == -1;
}

// Operation function
double operate(double leftOpnd, double rightOpnd, char opr){
  double result = 0.0;
  switch(opr){
    case '+': return leftOpnd + rightOpnd; printf("%lf\n", leftOpnd + rightOpnd); break;
    case '-': return leftOpnd - rightOpnd; break;
    case '*': return leftOpnd * rightOpnd; break;
    case '/': return leftOpnd / rightOpnd; break;
    case '$': return pow(leftOpnd,rightOpnd); break;
    default: printf("%c is not a valid operator\n", opr); exit (1);
  }
}

double evalPrefix(char prefix[]){
  OperandStack stack;
  ExpressionStack temp;
  stack.top = -1;
  temp.top = -1;
  int i = 0;
  while(prefix[i] != '\0'){
    pushc(&temp, prefix[i]);
    i++;
  }
  while(temp.top != -1){
    char token = popc(&temp);
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
  }
  return pop(&stack);
}

int main() {
  char prefix[SIZE];
  printf("Enter the prefix expression: ");
  scanf("%s", prefix);
  double result = evalPrefix(prefix);
  printf("Result: %lf\n", result);
  return 0;
}
