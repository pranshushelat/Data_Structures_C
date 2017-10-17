/*
 * File:   Double Ended Queue
 * Author: Pranshu Shelat
 *
 * Created on: October 14, 2017
 *
 * Details: This program creates a double ended queue for storing values
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
void enqueueRear(Queue *, int);
void enqueueFront(Queue *, int);
int dequeueRear(Queue *);
int dequeueFront(Queue *);

// function to print menu
void menu(){
  printf("         Double Ended Queue         \n");
  printf("------------------------------------\n");
  printf("Queue of length '%d' is created\n", SIZE);
  printf("Please choose the appropriate option\n");
  printf("1. Enqueue at Rear\n");
  printf("2. Enqueue at Front\n");
  printf("3. Dequeue from Rear\n");
  printf("4. Dequeue from Front\n");
  printf("5. Exit\n");
  printf("------------------------------------\n");
}

// initialize a queue
void initQueue(Queue *q){
  q->front = 0;
  q->rear = -1;
}

// enqueue at rear operation
void enqueueRear(Queue * q, int val){
  if(q->rear == SIZE - 1){
    printf("Unable to insert at rear!\n");
    return;
  }
  q->rear++;
  q->item[q->rear] = val;
}

// enqueue at front operation
void enqueueFront(Queue * q, int val){
  if(q->front == 0){
    printf("Unable to insert at front!\n");
    return;
  }
  q->front--;
  q->item[q->front] = val;
}

// dequeue from rear operation
int dequeueRear(Queue *q){
  if(q->front > q->rear){
    printf("Queue Underflow\n");
    return -99;
  }
  return q->item[q->rear--];
}

// dequeue from front operation
int dequeueFront(Queue *q){
  if(q->front > q->rear){
    printf("Queue Underflow\n");
    return -99;
  }
  return q->item[q->front++];
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
            enqueueRear(&q, val);
            break;
      case 2:
            printf("Input value: ");
            scanf("%d", &val);
            enqueueFront(&q, val);
            break;
      case 3:
            val = dequeueRear(&q);
            if(val != -99){
              printf("Output value: %d\n", val);
            }
            break;
      case 4:
            val = dequeueFront(&q);
            if(val != -99){
              printf("Output value: %d\n", val);
            }
            break;
      case 5:
            quit = 1;
            break;
      default:
            printf("Invalid choice, valid options are 1-5\n");
    }
  }
  return 0;
}
