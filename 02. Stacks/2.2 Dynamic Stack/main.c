#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *item;
  int top;
  int size;
} stack;

void init(stack *, int);
void menu();
void push(stack *, int);
int pop(stack *);
void deallocate(stack *);
int getSize(stack *);
void getBinary(unsigned int);

int main(){
  int size, choice, val;
  unsigned int number;
  stack s;
  init(&s, 3);

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
      case 4:
          printf("Size of the stack: %d\n", getSize(&s));
          break;
      case 5:
          printf("Enter value: ");
          scanf("%d",&number);
          getBinary(number);
          break;
      default:
          printf("Invalid choice\n");
          break;
    }
  }
  return 0;
}

void init(stack *sp, int size){
  sp->top = -1;
  sp->item = (int *)calloc(size, sizeof(int));
  if(sp->item == NULL){
    printf("Unable to allocate memory");
    exit(1);
  }
  sp->size = size;
}

void menu(){
  printf("1. Push\n");
  printf("2. Pop\n");
  printf("3. Exit\n");
  printf("4. Size of stack\n");
  printf("5. Convert Decimal to Binary\n");
}

void push(stack *sp, int val){
  if(sp->top == sp->size - 1){
    int *temp, i;
    temp = (int *)calloc(sp->size * 2, sizeof(int));
    if(temp == NULL)
      printf("Stack Overflow\n");
    for(i=0; i<=sp->top; temp[i] = sp->item[i], i++);
    free(sp->item);
    sp->item = temp;
    sp->size *= 2;
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
    sp->size = 0;
  }
}

int getSize(stack *sp){
  return sp->size;
}

void getBinary(unsigned int data){
  stack db;
  init(&db, 4);
  int hold = data;
  do{
    push(&db, hold%2);
    hold = hold/2;
  }while(hold > 0);
  printf("The binary equivalent is : ");
  while(db.top != -1){
    printf("%d", pop(&db));
  }
  printf("\n");
  deallocate(&db);
}
