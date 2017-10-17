/*
 * File:   Binary Search Tree
 * Author: Pranshu Shelat
 *
 * Created on: October 16, 2017
 *
 * Details: This program creates a binary search tree and
 *          implements basic functions like insert, search & print
 */

#include <stdio.h>
#include <stdlib.h>

// struct for the node
typedef struct Node {
 int data;
 struct Node *left;
 struct Node *right;
} Node;

// initialize root
void init(Node *key)
{
  key->left = NULL;
  key->right = NULL;
  key->data = 0;
}

// create new node to be inserted
Node * newNode(int data){
  Node *newNodePtr = (Node *) malloc(sizeof (Node));
  if (newNodePtr == NULL) {
    printf("Unable to allocate new node\n");
    exit(1);
  }
  newNodePtr->data = data;
  newNodePtr->left = NULL;
  newNodePtr->right = NULL;
  return newNodePtr;
}

// insert the created node at appropriate location
Node * insertData(Node *key, int data){
 if(key == NULL){
   key = newNode(data);
   return key;
 }
 else if(data <= key->data){
   key->left = insertData(key->left, data);
 }
 else{
   key->right = insertData(key->right, data);
 }
 return key;
}

// print all values using inorder traversal
void inorder(Node *key){
  if(key!=NULL){
    inorder(key->left);
    printf("%d ", key->data);
    inorder(key->right);
  }
}

// level order traversal
  // size of the queue
  #define SIZE 100

  // queue structure
  typedef struct {
    Node * item[SIZE];
    int front, rear;
  } Queue;

  // initialize a queue
  void initQueue(Queue *q){
    q->front = SIZE - 1;
    q->rear = SIZE - 1;
  }

  // enqueue operation
  void enqueue(Queue * q, Node * key){
    if((q->rear+1)%SIZE == q->front){
      printf("Queue Overflow\n");
      return;
    }
    q->rear = (q->rear+1)%SIZE;
    q->item[q->rear] = key;
  }

  // dequeue operation
  Node * dequeue(Queue *q){
    if(q->front == q->rear){
      printf("Queue Underflow\n");
      return NULL;
    }
    q->front = (q->front + 1) % SIZE;
    return q->item[q->front];
  }

  // print values
  void levelorder(Node * key){
    if(key == NULL){
      printf("Tree is empty\n");
      return;
    }
    Queue q;
    initQueue(&q);
    enqueue(&q,key);
    while(q.front != q.rear){
      key = dequeue(&q);
      printf("%d  ", key->data);
      if(key->left != NULL) enqueue(&q,key->left);
      if(key->right != NULL) enqueue(&q,key->right);
    }
  }

// load predefined values from a file
Node * loadFromFile(Node *key, char *fileName){
  FILE *inputFile = fopen(fileName, "r");
  if (inputFile == NULL){
    return NULL;
  }
  int data;
  while(!feof(inputFile)){
    fscanf(inputFile, "%d", &data);
    key = insertData(key, data);
  }
  fclose(inputFile);
  return key;
}

// search a particular value
void searchData(Node *key, int data){
  while(key->data != data){
    if(key != NULL){
      printf("  %d ->",key->data);
      if(key->data > data){
          key = key->left;
       }
       else{
          key = key->right;
       }
       if(key == NULL){
          printf("  Element not found\n");
          return;
       }
     }
  }
  printf(" %d\nElement found!\n", data);
}

// minimum and maximum
int min(Node * key){
  if(key == NULL){
    printf("Tree is empty\n");
  }
  while(key->left != NULL){
    key = key->left;
  }
  return key->data;
}
int max(Node * key){
  if(key == NULL){
    printf("Tree is empty\n");
  }
  while(key->right != NULL){
    key = key->right;
  }
  return key->data;
}

// delete a particular value
Node * deleteData(Node *key, int data){
  if(key == NULL) return key;
  else if(data < key->data) key->left = deleteData(key->left, data);
  else if(data > key->data) key->right = deleteData(key->right, data);
  else{
    if(key->left == NULL && key->right == NULL){
      free(key);
      key = NULL;
    }
    else if(key->left == NULL){
      Node * temp = key;
      key = key->right;
      free(temp);
    }
    else if(key->right == NULL){
      Node * temp = key;
      key = key->left;
      free(temp);
    }
    else{
      int temp = min(key->right);
      key->data = temp;
      key->right = deleteData(key->right, temp);
    }
    return key;
  }
}

// print a menu for list of actions
void menu(){
  printf("     Binary Search Tree     \n");
  printf("----------------------------\n");
  printf("1. Load from file\n");          // load integer data from file
  printf("2. Insert Value\n");            // insert a value in tree
  printf("3. Print Values Inorder\n");    // inorder traversal the values in tree
  printf("4. Print Values Level Order\n");// level traversal the values in tree
  printf("5. Search Value\n");            // search a particular value
  printf("6. Minimum Value\n");           // find minimum and maximum values
  printf("7. Maximum Value\n");           // find minimum and maximum values
  printf("8. Delete Value\n");
  printf("9. Quit\n");                    // to exit the program
}

int main(){
  Node *root=NULL;
  // init(root);
  int choice, data, quit = 0;
  menu();
  while (!quit) {
    printf("Please input your choice: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
            root = loadFromFile(root, "data.txt");
            if (root != NULL)
              printf("File has been loaded successfully\n");
            else
              printf("There was some error while loading and creating the list\n");
            break;
      case 2:
            printf("Input data: ");
            scanf("%d", &data);
            root = insertData(root, data);
            break;
      case 3:
            printf("Values in the tree: ");
            inorder(root);
            printf("\n");
            break;
      case 4:
            printf("Values in the tree: ");
            levelorder(root);
            printf("\n");
            break;
      case 5:
            printf("Enter the value to search: ");
            scanf("%d", &data);
            searchData(root, data);
            break;
      case 6:
            data = min(root);
            if(data != -99){
              printf("Minimum Value is %d\n", data);
            }
            else printf("There was a problem while running the funtion\n");
            break;
      case 7:
            data = max(root);
            if(data != -99){
              printf("Maximum Value is %d\n", data);
            }
            else printf("There was a problem while running the funtion\n");
            break;
      case 8:
            printf("Enter the value to delete: ");
            scanf("%d", &data);
            deleteData(root, data);
            break;
      case 9:
            quit = 1;
            break;
      default:
            printf("Invalid option chosen, valid option is from 1 - 4\n");
    }
  }
  return 0;
}
