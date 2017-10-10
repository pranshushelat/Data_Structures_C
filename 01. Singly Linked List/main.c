/*
      Data Structures: Singly Linked List
      Author: Pranshu Shelat
      Purpose: Detailing various operations that can be performed
               in a singly linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  struct Node *head;
  struct Node *tail;
  int nodeCount;
} LinkedList;

//function declarations
void initList(LinkedList *);
int loadFromFile(LinkedList *, char *);
void createList(LinkedList *);
void insertAtHead(LinkedList *, int);
void insertAtTail(LinkedList *, int);
void printListDetail(LinkedList *);
void printList(LinkedList *);
Node * find(LinkedList *, int);
int deleteFirst(LinkedList *);
int deleteLast(LinkedList *);
int deleteTarget(LinkedList *, int);
void reverse(LinkedList *);
void createRandomList(LinkedList *, int);

void menu() {
  printf("     Single Linked List Operations     \n");
  printf("---------------------------------------\n");
  printf("1. Load from file\n");
  printf("2. Insert at head\n");
  printf("3. Insert at tail\n");
  printf("4. Print List (detail)\n");
  printf("5. Print List (data only)\n");
  printf("6. Find\n");
  printf("7. Delete first\n");
  printf("8. Delete last\n");
  printf("9. Delete a target node\n");
  printf("10. Reverse\n");
  printf("11. Create a list of random numbers\n");
  printf("12. Quit\n");
}

void initList(LinkedList *lstPtr) {
  lstPtr->head = NULL;
  lstPtr->tail = NULL;
  lstPtr->nodeCount = 0;
}

int main() {
  LinkedList list;
  initList(&list);
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
      success = loadFromFile(&list,"data.txt");
      if(success == 1)
      printf("File has been loaded successfully\n");
      else
      printf("There was an error loading file\n");
      break;

      case 2:
      printf("Input data to insert at head (as first node): ");
      scanf("%d", &data);
      insertAtHead(&list, data);
      break;

      case 3:
      printf("Input data to insert at tail (as last node): ");
      scanf("%d", &data);
      insertAtTail(&list, data);
      break;

      case 4:
      printListDetail(&list);
      break;

      case 5:
      printList(&list);
      break;

      case 6:
      printf("Enter target to find: ");
      scanf("%d", &data);
      current = find(&list, data);
      if (current == NULL){
        printf("Target not found in the Linkedlist\n");
      }
      else{
        printf("Target node exists, address of the target node: %p\n", current);
      }
      break;

      case 7:
      data = deleteFirst(&list);
      if (data != -99) {
        printf("The value %d was deleted from the first node\n",data);
      }
      else{
        printf("The list was empty\n");
      }
      break;

      case 8:
      data = deleteLast(&list);
      if (data != -99) {
        printf("The value %d was deleted from the last node\n",data);
      }
      else{
        printf("The list was empty\n");
      }
      break;

      case 9:
      printf("Enter target to find: ");
      scanf("%d", &data);
      success = deleteTarget(&list,data);
      if(success == 0){
        printf("No such target found\n");
      }
      else{
        printf("The target node was deleted\n");
      }
      break;

      case 10:
      reverse(&list);
      break;

      case 11:
      printf("Enter of the number of elements needed in list: ");
      scanf("%d", &n);
      createRandomList(&list, n);
      break;

      case 12:
      quit = 1;
      break;

      default:
      printf("Invalid option chosen, valid option is from 1 - 11\n");
    }
  }
  return 0;
}

void insertAtTail(LinkedList *lstPtr, int data) {
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  if (lstPtr->nodeCount == 0) {
    lstPtr->head = newNodePtr;
    lstPtr->tail = newNodePtr;
  } else {
    lstPtr->tail->next = newNodePtr;
    lstPtr->tail = newNodePtr;
  }
  lstPtr->nodeCount++;
}

void insertAtHead(LinkedList *lstPtr, int data) {
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  if (lstPtr->nodeCount == 0) {
    lstPtr->head = newNodePtr;
    lstPtr->tail = newNodePtr;
  } else {
    newNodePtr->next = lstPtr->head;
    lstPtr->head = newNodePtr;
  }
  lstPtr->nodeCount++;
}

void printList(LinkedList *lstPtr) {
  if (lstPtr->nodeCount == 0) {
    printf("Linked List is empty\n");
    return;
  }
  Node *current = lstPtr->head;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
  }
}

void printListDetail(LinkedList *lstPtr) {
  if (lstPtr->nodeCount == 0) {
    printf("Linked List is empty\n");
    return;
  }
  printf("Printing linked list in detail\n");
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

Node * find(LinkedList *lstPtr, int target)
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

int loadFromFile(LinkedList *lstPtr, char *fileName)
{
  FILE *inputFile = fopen(fileName, "r");
  if(inputFile == NULL){
    return 0;
  }
  int data;
  fscanf(inputFile, "%d", &data);
  while(!feof(inputFile)){
    insertAtTail(lstPtr, data);
    fscanf(inputFile, "%d", &data);
  }
  fclose(inputFile);
  return 1;
}

int deleteFirst(LinkedList *lstPtr){
  if(lstPtr->nodeCount == 0){
    return -99;
  }
  Node *first = lstPtr->head;
  int data = first->data;
  if(lstPtr->nodeCount == 1){
    lstPtr->head = NULL;
    lstPtr->tail = NULL;
  }
  else{
    lstPtr->head = first->next;
  }
  free(first);
  lstPtr->nodeCount--;
  return data;
}

int deleteLast(LinkedList *lstPtr){
  if(lstPtr->nodeCount == 0){
    return -99;
  }
  Node *current = lstPtr->head;
  Node *last = lstPtr->tail;
  int data = last->data;
  if(lstPtr->nodeCount == 1){
    lstPtr->head = NULL;
    lstPtr->tail = NULL;
  }
  else{
    while(current->next != lstPtr->tail){
      current = current->next;
    }
    lstPtr->tail = current;
    lstPtr->tail->next = NULL;
  }
  free(last);
  lstPtr->nodeCount--;
  return data;
}

int deleteTarget(LinkedList *lstPtr, int target)
{
  Node* current = lstPtr->head;
  if(current == NULL)
  return 0;
  if(current->data == target){
    deleteFirst(lstPtr);
    return 1;
  }
  while(current->next != NULL){
    if(current->next->data == target)
    break;
    current = current->next;
  }
  if(current->next->next == NULL){
    deleteLast(lstPtr);
    return 1;
  }
  current->next = current->next->next;
  lstPtr->nodeCount--;
  return 1;
}

void reverse(LinkedList *lstPtr)
{
  if(lstPtr->head == NULL){
    printf("The list is empty\n");
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

void createRandomList(LinkedList *lstPtr, int data)
{
  int i;
  srand(time(NULL));
    for(i = 1; i<=data; ++i){
    int k = rand() % 100;
    insertAtTail(lstPtr, k);
  }
}
