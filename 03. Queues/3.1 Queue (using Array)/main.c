/*
 * File:   Queue
 * Author: Pranshu Shelat
 *
 * Created on: October 14, 2017
 *
 * Details: This program creates a fixed length FIFO queue for storing values
 */

#include <stdio.h>
#include <stdlib.h>

// size of the queue
#define SIZE 10

// queue structure
typedef struct {
  int item[SIZE];
  int front, rear;
} Queue;

// function prototypes
void menu();
void initQueue(Queue *);
void enqueue(Queue *, int);
int dequeue(Queue *);

// function to print menu
void menu(){
  printf("   FIFO Queue (using Linked queue)   \n");
  printf("-------------------------------------\n");
  printf("Queue of length '%d' is created\n", SIZE);
  printf("Please choose the appropriate option\n");
  printf("1. Enqueue\n");
  printf("2. Dequeue\n");
  printf("3. Exit\n");
  printf("-------------------------------------\n");
}

// initialize a queue
void initQueue(Queue *q){
  q->front = SIZE - 1;
  q->rear = SIZE - 1;
}

// enqueue operation
void enqueue(Queue * q, int val){
  if((q->rear+1)%SIZE == q->front){
    printf("Queue Overflow\n");
    return;
  }
  q->rear = (q->rear+1)%SIZE;
  q->item[q->rear] = val;
}

// dequeue operation
int dequeue(Queue *q){
  if(q->front == q->rear){
    printf("Queue Underflow\n");
    return -99;
  }
  q->front = (q->front + 1) % SIZE;
  return q->item[q->front];
}

int main(){
  Queue q;
  initQueue(&q);
  int c, val, quit = 0;
  menu();
  while(!quit){
    printf("Enter your choice: ");
    scanf("%d", &c);
    switch (c) {
      case 1:
            printf("Input value: ");
            scanf("%d", &val);
            enqueue(&q, val);
            break;
      case 2:
            val = dequeue(&q);
            if(val != -99){
              printf("Output value: %d\n", val);
            }
            break;
      case 3:
            quit = 1;
            break;
      default:
            printf("Invalid choice, valid options are 1-3\n");
    }
  }
  return 0;
}
