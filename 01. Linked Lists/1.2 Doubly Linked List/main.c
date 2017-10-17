/*
      Data Structures: Doubly Linked List
      Author: Pranshu Shelat
      Purpose: Detailing various operations that can be performed
               in a doubly linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct DblList {
  struct Node *head;
  struct Node *tail;
  int nodeCount;
} DblList;

void initList(DblList *lstPtr)
{
  lstPtr->head = NULL;
  lstPtr->tail = NULL;
  lstPtr->nodeCount = 0;
}

void addFirst(DblList *lstPtr, int data)
{
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  newNodePtr->prev = NULL;
  if(lstPtr->nodeCount == 0){
    lstPtr->head = newNodePtr;
    lstPtr->tail = newNodePtr;
  }
  else{
    newNodePtr->next = lstPtr->head;
    lstPtr->head->prev = newNodePtr;
    lstPtr->head = newNodePtr;
  }
  lstPtr->nodeCount++;
}

void addLast(DblList *lstPtr, int data)
{
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  newNodePtr->prev = NULL;
  if(lstPtr->nodeCount == 0){
    lstPtr->head = newNodePtr;
    lstPtr->tail = newNodePtr;
  }
  else{
    newNodePtr->prev = lstPtr->tail;
    lstPtr->tail->next = newNodePtr;
    lstPtr->tail = newNodePtr;
  }
  lstPtr->nodeCount++;
}

int loadFromFile(DblList *lstPtr, char *fileName){
  FILE *inputFile = fopen(fileName, "r");
  if (inputFile == NULL){
    return 0;
  }
  int data;
  fscanf(inputFile, "%d", &data);
  while(!feof(inputFile)){
    addLast(lstPtr, data);
    fscanf(inputFile, "%d", &data);
  }
  fclose(inputFile);
  return 1;

}

void createListFromRandomNumbers(DblList *lstPtr, int n){
  int i;
  srand(time(NULL));

  for(i = 1; i<=n; ++i){
      int k = rand() % 100;
      addLast(lstPtr, k);
  }
}

void printListDetail(DblList *lstPtr){
  if(lstPtr->nodeCount == 0){
    printf("The list is empty\n");
    return;
  }
  Node *current = lstPtr->head;
  printf("\nHead: %p\n", lstPtr->head);
  printf(" Current    Previous  | Val  |    Next\n");
  while(current != NULL){
    printf("(%p) [%p  |  %d  |  %p]\n", current, current->prev, current->data, current->next);
    current = current->next;
  }
  printf("Tail: %p\n", lstPtr->tail);
}

void printForward(DblList *lstPtr){
  if(lstPtr->nodeCount == 0){
    printf("The list is empty\n");
    return;
  }
  Node *current = lstPtr->head;
  while(current != NULL){
    printf("%4d ", current->data);
    current = current->next;
  }
  printf("\n");
}

void printReverse(DblList *lstPtr){
  if(lstPtr->nodeCount == 0){
    printf("The list is empty\n");
    return;
  }
  Node *current = lstPtr->tail;
  while(current != NULL){
    printf("%4d ", current->data);
    current = current->prev;
  }
  printf("\n");
}

Node * find(DblList *lstPtr, int target){
  Node *current;
  current = lstPtr->head;
  while(current != NULL){
    if(current->data == target){
      return current;
    }
    current = current->next;
  }
  return NULL;
}

int insertAfter(DblList *lstPtr, int target, int data){
  Node *current = find(lstPtr,target);
  if(current == NULL){
    printf("Invalid target\n");
    return 0;
  }
  if(current == lstPtr->tail){
    addLast(lstPtr, data);
  }
  else{
    Node *newNodePtr = (Node *)malloc(sizeof(Node));
    if(newNodePtr == NULL){
      printf("Unable to create node\n");
      return 0;
    }
    newNodePtr->data = data;
    newNodePtr->prev = current;
    newNodePtr->next = current->next;
    current->next = newNodePtr;
    newNodePtr->next->prev = newNodePtr;
    lstPtr->nodeCount++;
  }
  return 1;
}

int insertBefore(DblList *lstPtr, int target, int data){
  Node *current = find(lstPtr,target);
  if(current == NULL){
    printf("Invalid target\n");
    return 0;
  }
  if(current == lstPtr->head){
    addFirst(lstPtr, data);
  }
  else{
    Node *newNodePtr = (Node *)malloc(sizeof(Node));
    if(newNodePtr == NULL){
      printf("Unable to create node\n");
      return 0;
    }
    newNodePtr->data = data;
    newNodePtr->prev = current->prev;
    newNodePtr->next = current;
    current->prev = newNodePtr;
    newNodePtr->prev->next = newNodePtr;
    lstPtr->nodeCount++;
  }
  return 1;
}

int deleteFirst(DblList *lstPtr){
  if(lstPtr->nodeCount == 0){
    return 0;
  }
  Node *temp = lstPtr->head;
  if(lstPtr->nodeCount == 1){
    lstPtr->head = lstPtr->tail = NULL;
  }
  else{
    lstPtr->head = lstPtr->head->next;
    lstPtr->head->prev = NULL;
  }
  free(temp);
  lstPtr->nodeCount--;
  return 1;
}

int deleteLast(DblList *lstPtr){
  if(lstPtr->nodeCount == 0){
    return 0;
  }
  Node *temp = lstPtr->tail;
  if(lstPtr->nodeCount == 1){
    lstPtr->head = lstPtr->tail = NULL;
  }
  else{
    lstPtr->tail = lstPtr->tail->prev;
    lstPtr->tail->next = NULL;
  }
  free(temp);
  lstPtr->nodeCount--;
  return 1;
}

int deleteTarget(DblList *lstPtr, int target){
  Node *temp = find(lstPtr, target);
  if(temp == NULL){
    return 0;
  }
  if(temp == lstPtr->head)
    return deleteFirst(lstPtr);
  if(temp == lstPtr->tail)
    return deleteLast(lstPtr);
  temp->prev->next = temp->next;
  temp->next->prev = temp->prev;
  free(temp);
  lstPtr->nodeCount--;
  return 1;
}

void reverseList(DblList *lstPtr){
  if(lstPtr->nodeCount == 0){
    printf("List is empty\n");
    return;
  }
  Node *temp1 = lstPtr->head;
  Node *temp2 = NULL;
  while(temp1 != NULL){
    temp2 = temp1->next;
    temp1->next = temp1->prev;
    temp1->prev = temp2;
    temp1 = temp2;
  }
  temp1 = lstPtr->head;
  lstPtr->head = lstPtr->tail;
  lstPtr->tail = temp1;
}

void menu(){
  printf("    Doubly Linked List Operations\n");
  printf("----------------------------------------\n");
  printf("1. Load from file\n");          // load integer data from file and will create the list by using insert_at_tail operation (menu option 3)
  printf("2. Create list with random numbers\n");
  printf("3. Add First\n");          // inserting a new node as the first node
  printf("4. Add Last\n");          // inserting a new node as the last node
  printf("5. Print List (detail)\n");     // printing the linked list in details, including the data and pointer in each node
  printf("6. Print List first to last (data only)\n");  // prints the integer data in each node from the first node to last
  printf("7. Print List last to first (data only)\n");  // prints data fro last to the first node
  printf("8. Find\n");                    // finds if an integer exisits in a node from the start in the list
  printf("9. Insert After\n");
  printf("10. Insert Before\n");
  printf("11. Delete first\n");            // deletes the first node
  printf("12. Delete last\n");             // deletes the last node
  printf("13. Delete a target node\n");    // deletes a particular node, if that exists
  printf("14. Reverse linked list\n");     // reverse the contents of list
  printf("15. Quit\n");                   // to terminate each node
}

int main(){
  DblList list;
  initList(&list);
  int choice;
  menu();
  int quit = 0;
  int data, n, target;
  int success;
  Node *current = NULL, *prev = NULL;
  while(!quit){
    printf("Please input your choice: ");
    scanf("%d", &choice);

    switch(choice){
      case 1:
            success = loadFromFile(&list, "data.txt");
            if (success == 1)
              printf("File has been loaded successfully\n");
            else
              printf("There was some error while loading and creating the list\n");
            break;
      case 2:
            printf("Enter number of integers to be generated and added into the list: ");
            scanf("%d", &n);
            createListFromRandomNumbers(&list, n);
            break;
      case 3:
            printf("Input data to insert at head (as first node): ");
            scanf("%d", &data);
            addFirst(&list, data);
            break;
      case 4:
            printf("Input data to insert at tail (as last node): ");
            scanf("%d", &data);
            addLast(&list, data);
            break;
      case 5:
            printListDetail(&list);
            break;
      case 6:
            printForward(&list);
            break;
      case 7:
            printReverse(&list);
            break;
      case 8:
            printf("Enter target: ");
            scanf("%d", &target);
            current = find(&list, target);
            if(current == NULL)
              printf("LinkedList doen not contain the target specified\n");
            else
              printf("Target exists in the linkedlist\n");
            break;
      case 9:
            printf("Enter target: ");
            scanf("%d", &target);
            printf("Input data: ");
            scanf("%d", &data);
            if (insertAfter(&list, target, data) == 1){
              printf("Insert after was successful\n");
            }
            else{
              printf("Insert after failed\n");
            }
            break;
      case 10:
            printf("Enter target: ");
            scanf("%d", &target);
            printf("Input data: ");
            scanf("%d", &data);
            if (insertBefore(&list, target, data) == 1){
              printf("Insert before was successful\n");
            }
            else{
              printf("Insert before failed\n");
            }
            break;
      case 11:
            if (deleteFirst(&list))
              printf("First node deleted successfully\n");
            else
              printf("Unable to delete first node\n");
            break;
      case 12:
            if (deleteLast(&list))
              printf("Last node deleted successfully\n");
            else
              printf("Unable to delete last node\n");
            break;
      case 13:
            printf("Enter target: ");
            scanf("%d", &target);
            if (deleteTarget(&list, target))
              printf("Target node deleted successfully\n");
            else
              printf("Unable to delete the target node, target may not be available\n");
            break;
      case 14:
            reverseList(&list);
            break;
      case 15:
            quit = 1;
            break;
      default:
            printf("Invalid option chosen, valid option is from 1 - 14\n");
    }
  }
  return 0;
}
