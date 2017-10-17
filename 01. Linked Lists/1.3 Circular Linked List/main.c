/*
      Data Structures: Circular Linked List
      Author: Pranshu Shelat
      Purpose: Detailing various operations that can be performed
               in a circular linked list
      Please note that here, we have a tail at points at the end
      of the list rather than a head pointing at the beginning
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  struct Node *tail;
  int nodeCount;
} LinkedList;

//function declarations
void initList(LinkedList *);              // to initialize a list
int loadFromFile(LinkedList *, char *);   // get the data from an external file
void insertAtBeginning(LinkedList *, int);// insert the new element after the tail
void insertAtEnd(LinkedList *, int);      // insert the new element before the tail
void printListDetail(LinkedList *);       // print all the elements with addresses
void printList(LinkedList *);             // print all the elements only
Node * find(LinkedList *, int);           // find a particular element
int deleteFirst(LinkedList *);            // delete the first node
int deleteLast(LinkedList *);             // delete the last node
int deleteTarget(LinkedList *, int);      // delete the targeted node
void createRandomList(LinkedList *, int); // create a list with specified amount of random elements

void menu() {
  printf("     Circular Linked List Operations     \n");
  printf("-----------------------------------------\n");
  printf("1. Load from file\n");
  printf("2. Insert at head\n");
  printf("3. Insert at tail\n");
  printf("4. Print List (detail)\n");
  printf("5. Print List (data only)\n");
  printf("6. Find\n");
  printf("7. Delete first\n");
  printf("8. Delete last\n");
  printf("9. Delete a target node\n");
  printf("10. Create a list of random numbers\n");
  printf("11. Quit\n");
}

void initList(LinkedList *lstPtr) {
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
      insertAtBeginning(&list, data);
      break;

      case 3:
      printf("Input data to insert at tail (as last node): ");
      scanf("%d", &data);
      insertAtEnd(&list, data);
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
      printf("Enter of the number of elements needed in list: ");
      scanf("%d", &n);
      createRandomList(&list, n);
      break;

      case 11:
      quit = 1;
      break;

      default:
      printf("Invalid option chosen, valid option is from 1 - 11\n");
    }
  }
  return 0;
}

void insertAtEnd(LinkedList *lstPtr, int data) {
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  if (lstPtr->nodeCount == 0) {
    lstPtr->tail = newNodePtr;
    lstPtr->tail->next = newNodePtr->next = newNodePtr;
  }
  else {
    newNodePtr->next = lstPtr->tail->next;
    lstPtr->tail->next = newNodePtr;
    lstPtr->tail = newNodePtr;
  }
  lstPtr->nodeCount++;
}

void insertAtBeginning(LinkedList *lstPtr, int data) {
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  if (lstPtr->nodeCount == 0) {
    lstPtr->tail = newNodePtr;
    lstPtr->tail->next = newNodePtr->next = newNodePtr;
  }
  else {
    newNodePtr->next = lstPtr->tail->next;
    lstPtr->tail->next = newNodePtr;
  }
  lstPtr->nodeCount++;
}

void printList(LinkedList *lstPtr) {
  if (lstPtr->nodeCount == 0) {
    printf("Linked List is empty\n");
    return;
  }
  Node *current = lstPtr->tail->next;
  do {
    printf("%d\n", current->data);
    current = current->next;
  } while (current != lstPtr->tail->next);
}

void printListDetail(LinkedList *lstPtr) {
  if (lstPtr->nodeCount == 0) {
    printf("Linked List is empty\n");
    return;
  }
  printf("Printing linked list in detail\n");
  Node *current = lstPtr->tail->next;
  int counter = 1;
  printf(" Current    Val  |    Next\n");
  do {
    printf("%2d. (%p)  [%4d  |  %p]\n", counter, current, current->data, current->next);
    current = current->next;
    counter++;
  } while (current != lstPtr->tail->next);
  printf("Tail: %p\n", lstPtr->tail);
}

Node * find(LinkedList *lstPtr, int target)
{
  Node* current = lstPtr->tail->next;
  do{
    if (current->data == target){
      return current;
    }
    current = current->next;
  } while (current != lstPtr->tail->next);
  return NULL;
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
    insertAtEnd(lstPtr, data);
    fscanf(inputFile, "%d", &data);
  }
  fclose(inputFile);
  return 1;
}

int deleteFirst(LinkedList *lstPtr){
  if(lstPtr->nodeCount == 0){
    return -99;
  }
  Node *first = lstPtr->tail->next;
  int data = first->data;
  if(lstPtr->nodeCount == 1){
    lstPtr->tail->next = NULL;
    lstPtr->tail = NULL;
  }
  else{
    lstPtr->tail->next = first->next;
  }
  free(first);
  lstPtr->nodeCount--;
  return data;
}

int deleteLast(LinkedList *lstPtr){
  if(lstPtr->nodeCount == 0){
    return -99;
  }
  Node *current = lstPtr->tail->next;
  Node *last = lstPtr->tail;
  int data = last->data;
  if(lstPtr->nodeCount == 1){
    lstPtr->tail = NULL;
  }
  else{
    while(current->next != lstPtr->tail){
      current = current->next;
    }
    current->next = lstPtr->tail->next;
    lstPtr->tail = current;
  }
  free(last);
  lstPtr->nodeCount--;
  return data;
}

int deleteTarget(LinkedList *lstPtr, int target)
{
  Node* current = lstPtr->tail->next;
  if(current == NULL)
  return 0;
  if(current->data == target){
    deleteFirst(lstPtr);
    return 1;
  }
  if(lstPtr->tail->data == target){
    deleteLast(lstPtr);
    return 1;
  }
  do {
    if(current->next->data == target){
      current->next = current->next->next;
      lstPtr->nodeCount--;
      return 1;
    }
    current = current->next;
  } while(current->next != lstPtr->tail->next);
  return 0;
}

void createRandomList(LinkedList *lstPtr, int data)
{
  int i;
  srand(time(NULL));
    for(i = 1; i<=data; ++i){
    int k = rand() % 100;
    insertAtEnd(lstPtr, k);
  }
}
