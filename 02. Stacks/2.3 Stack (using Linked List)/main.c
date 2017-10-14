#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct stack {
  struct Node *head;
  struct Node *tail;
  int stackSize;
} stack;

//function declarations
void initStack(stack *);
int loadFromFile(stack *, char *);
void push(stack *, int);
void printStackDetail(stack *);
void printStack(stack *);
Node * find(stack *, int);
int pop(stack *);
void reverse(stack *);
void createRandomStack(stack *, int);

void menu() {
  printf("     Stack using Linked Stack     \n");
  printf("---------------------------------\n");
  printf("1. Load from file\n");
  printf("2. Push\n");
  printf("3. Print Stack (detail)\n");
  printf("4. Print Stack (data only)\n");
  printf("5. Find\n");
  printf("6. Pop\n");
  printf("7. Reverse the contents of stack\n");
  printf("8. Create a stack of random numbers\n");
  printf("9. Quit\n");
}

void initStack(stack *lstPtr) {
  lstPtr->head = NULL;
  lstPtr->tail = NULL;
  lstPtr->stackSize = 0;
}

int main() {
  stack s;
  initStack(&s);
  int choice;
  menu();
  int quit = 0;
  int data, n, target;
  int success;
  Node *current = NULL, *prev = NULL;

  while (!quit) {
    printf("Please input your choice: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
      success = loadFromFile(&s,"data.txt");
      if(success == 1)
      printf("File has been loaded successfully\n");
      else
      printf("There was an error loading file\n");
      break;

      case 2:
      printf("Input data to insert in stack: ");
      scanf("%d", &data);
      push(&s, data);
      break;

      case 3:
      printStackDetail(&s);
      break;

      case 4:
      printStack(&s);
      break;

      case 5:
      printf("Enter target to find: ");
      scanf("%d", &data);
      current = find(&s, data);
      if (current == NULL){
        printf("Target not found in the stack\n");
      }
      else{
        printf("Target node exists, address of the target node: %p\n", current);
      }
      break;

      case 6:
      data = pop(&s);
      if (data != -99) {
        printf("The value %d was popped\n",data);
      }
      else{
        printf("Stack Underflow\n");
      }
      break;

      case 7:
      reverse(&s);
      break;

      case 8:
      printf("Enter of the number of elements needed in s: ");
      scanf("%d", &n);
      createRandomStack(&s, n);
      break;

      case 9:
      quit = 1;
      break;

      default:
      printf("Invalid option chosen, valid option is from 1 - 11\n");
    }
  }
  return 0;
}

void push(stack *lstPtr, int data) {
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Stack Overflow\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  if (lstPtr->stackSize == 0) {
    lstPtr->head = newNodePtr;
    lstPtr->tail = newNodePtr;
  } else {
    newNodePtr->next = lstPtr->head;
    lstPtr->head = newNodePtr;
  }
  lstPtr->stackSize++;
}

void printStack(stack *lstPtr) {
  if (lstPtr->stackSize == 0) {
    printf("Linked Stack is empty\n");
    return;
  }
  Node *current = lstPtr->head;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
  }
}

void printStackDetail(stack *lstPtr) {
  if (lstPtr->stackSize == 0) {
    printf("Linked Stack is empty\n");
    return;
  }
  printf("Printing linked stack in detail\n");
  printf("Head: %p\n", lstPtr->head);
  Node *current = lstPtr->head;
  int counter = 1;
  while (current != NULL) {
    printf("%d. (%p)[%d|%p]\n", counter, current, current->data, current->next);
    current = current->next;
    counter++;
  }
  printf("Tail: %p\n", lstPtr->tail);
}

Node * find(stack *lstPtr, int target)
{
  Node* current = lstPtr->head;
  while(current!=NULL){
    if (current->data == target){
      break;
    }
    current = current->next;
  }
  return current;
}

int loadFromFile(stack *lstPtr, char *fileName)
{
  FILE *inputFile = fopen(fileName, "r");
  if(inputFile == NULL){
    return 0;
  }
  int data;
  fscanf(inputFile, "%d", &data);
  while(!feof(inputFile)){
    push(lstPtr, data);
    fscanf(inputFile, "%d", &data);
  }
  fclose(inputFile);
  return 1;
}

int pop(stack *lstPtr){
  if(lstPtr->stackSize == 0){
    return -99;
  }
  Node *first = lstPtr->head;
  int data = first->data;
  if(lstPtr->stackSize == 1){
    lstPtr->head = NULL;
    lstPtr->tail = NULL;
  }
  else{
    lstPtr->head = first->next;
  }
  free(first);
  lstPtr->stackSize--;
  return data;
}

void reverse(stack *lstPtr)
{
  if(lstPtr->head == NULL){
    printf("Stack Underflow\n");
    return;
  }
  Node *current = lstPtr->head;
  int *temp1 = NULL;
  int *temp2 = NULL;
  while(current != NULL){
    temp2 = (int *)current->next;
    current->next = (Node *)temp1;
    temp1 = (int *)current;
    current = (Node *)temp2;
  }
  lstPtr->tail = lstPtr->head;
  lstPtr->head = (Node *)temp1;
  printf("The reversal was successful\n");
}

void createRandomStack(stack *lstPtr, int data)
{
  int i;
  srand(time(NULL));
    for(i = 1; i<=data; ++i){
    int k = rand() % 100;
    push(lstPtr, k);
  }
}
