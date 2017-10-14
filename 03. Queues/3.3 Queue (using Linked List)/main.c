/*
 * File:   Queue using a Linked queue
 * Author: Pranshu Shelat
 *
 * Created on: October 14, 2017
 *
 * Details: This program creates a fixed length FIFO queue for
            storing values using a linked list
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Queue {
  struct Node *head;
  struct Node *tail;
  int nodeCount;
} Queue;

//function declarations
void initQueue(Queue *);
void enqueue(Queue *, int);
void printQueue(Queue *);
int dequeue(Queue *);

// function to print menu
void menu(){
  printf("   FIFO Queue (using Linked queue)   \n");
  printf("-------------------------------------\n");
  printf("Queue of length '%d' is created\n", SIZE);
  printf("Please choose the appropriate option\n");
  printf("1. Enqueue\n");
  printf("2. Dequeue\n");
  printf("3. Print Queue Values\n");
  printf("4. Exit\n");
  printf("-------------------------------------\n");
}

int main() {
  Queue q;
  initQueue(&q);
  int choice;
  menu();
  int quit = 0;
  int data;

  while (!quit) {
    printf("Please input your choice: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
            if(q.nodeCount != SIZE){
              printf("Enqueue: ");
              scanf("%d", &data);
              enqueue(&q, data);
            }
            else{
              printf("Queue Overflow\n");
            }
            break;
      case 2:
            data = dequeue(&q);
            if (data != -99) {
              printf("Value removed: %d\n",data);
            }
            else{
              printf("Queue Underflow\n");
            }
            break;
      case 3:
            printQueue(&q);
            break;
      case 4:
            quit = 1;
            break;

      default:
      printf("Invalid option chosen, valid option is from 1 - 4\n");
    }
  }
  return 0;
}

// initialize the linked list for queue
void initQueue(Queue *q) {
  q->head = NULL;
  q->tail = NULL;
  q->nodeCount = 0;
}

// add value at tail of linked list as enqueue operation
void enqueue(Queue *q, int data) {
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    return;
  }
  newNodePtr->data = data;
  newNodePtr->next = NULL;
  if (q->nodeCount == 0) {
    q->head = newNodePtr;
    q->tail = newNodePtr;
  } else {
    q->tail->next = newNodePtr;
    q->tail = newNodePtr;
  }
  q->nodeCount++;
}

// delete value from the head of linked list as dequeue operation
int dequeue(Queue *q){
  if(q->nodeCount == 0){
    return -99;
  }
  Node *first = q->head;
  int data = first->data;
  if(q->nodeCount == 1){
    q->head = NULL;
    q->tail = NULL;
  }
  else{
    q->head = first->next;
  }
  free(first);
  q->nodeCount--;
  return data;
}

// print all the values of queue
void printQueue(Queue *q) {
  if (q->nodeCount == 0) {
    printf("The queue is empty\n");
    return;
  }
  Node *current = q->head;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
  }
}
