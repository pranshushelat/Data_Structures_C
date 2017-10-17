#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int item[10];
  int top;
} stack;

void init(stack *);
void menu();
void push(stack *, int);
int pop(stack *);
void deallocate(stack *);
void getBinary(unsigned int);

int main(){
  int choice, val;
  unsigned int number;
  stack s;
  init(&s);

  menu();

  while(1){
    printf("Enter choice: ");
    scanf("%d", &choice);
    switch(choice){
      case 1:
          printf("Enter value: ");
          scanf("%d", &val);
          push(&s,val);
          break;
      case 2:
          val = pop(&s);
          if(val != -9999){
            printf("Value deleted: %d\n", val);
          }
          break;
      case 3:
          deallocate(&s);
          exit(0);
      default:
          printf("Invalid choice\n");
          break;
    }
  }
  return 0;
}

void init(stack *sp){
  sp->top = -1;
  if(sp->item == NULL){
    printf("Unable to allocate memory");
    exit(1);
  }
  printf("Stack of size 10 created\n");
}

void menu(){
  printf("1. Push\n");
  printf("2. Pop\n");
  printf("3. Exit\n");
}

void push(stack *sp, int val){
  if(sp->top >= 9){
    printf("Stack Overflow\n");
    return;
  }
  sp->top++;
  sp->item[sp->top] = val;
}

int pop(stack *sp){
  if(sp->top == -1){
    printf("Stack Underflow\n");
    return -9999;
  }
  int val;
  val = sp->item[sp->top];
  sp->top--;
  return val;
}

void deallocate(stack *sp){
  if(sp->item == NULL){
    free(sp->item);
    sp->top = -1;
  }
}
