#include "board.h"

typedef struct node {
  board * b;
  // Lower values indicate higher priority 
  int priority;
  struct node * next;

}
Node;

// Function to Create A New Node 
Node * newNode(board * brd) {
  Node * temp = (Node * ) malloc(sizeof(Node));
  temp -> b = brd;
  temp -> priority = brd -> cost + brd -> level;
  temp -> next = NULL;
  return temp;
}

// Return the value at head 
board * peek(Node ** head) {
  return ( * head) -> b;
}

// Removes the element with the 
// highest priority form the list 
void pop(Node ** head) {
  Node * temp = * head;
  ( * head) = ( * head) -> next;
  free(temp);
}

// Function to push according to priority 
void push(Node ** head, board * d) {
  Node * start = ( * head);
  // Create new Node 
  Node * temp = newNode(d);
  int p = d -> cost + d -> level;
  // Special Case: The head of list has lesser 
  // priority than new node. So insert new 
  // node before head node and change head node. 
  if (( * head) -> priority > p) {
    // Insert New Node before head 
    temp -> next = * head;
    ( * head) = temp;
  } else {

    // Traverse the list and find a 
    // position to insert new node 
    while (start -> next != NULL && start -> next -> priority < p) {
      start = start -> next;
    }

    // Either at the ends of the list 
    // or at required position 
    temp -> next = start -> next;
    start -> next = temp;
  }
}

// Function to check is list is empty 
int isEmpty(Node ** head) {
  return ( * head) == NULL;
}
void pushNeighbors(board * brd, Node * pq) {
  int i, j, stop = 0;
  int ** temp, ** t;
  allocate_mem( & temp);
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++)
      if (brd -> data[i][j] == 0) {
        stop = 1;
        break;
      }
    if (stop == 1) break;
  }
  if (i + 1 < N) {
    copy(temp, brd -> data);
    swap(temp, i + 1, j, i, j);
    board * dChild = newBoard(temp, brd, brd -> level + 1);
    if (pq == NULL) {
      pq = newNode(dChild);
    } else
      push( & pq, dChild);
  }
  if (j - 1 >= 0) {
    copy(temp, brd -> data);
    swap(temp, i, j - 1, i, j);
    board * lChild = newBoard(temp, brd, brd -> level + 1);
    if (pq == NULL) {
      pq = newNode(lChild);
    } else
      push( & pq, lChild);
  }
  if (i - 1 >= 0) {
    copy(temp, brd -> data);
    swap(temp, i - 1, j, i, j);
    board * uChild = newBoard(temp, brd, brd -> level + 1);
    if (pq == NULL) {
      pq = newNode(uChild);
    } else
      push( & pq, uChild);
  }

  if (j + 1 < N) {
    copy(temp, brd -> data);
    swap(temp, i, j + 1, i, j);
    board * rChild = newBoard(temp, brd, brd -> level + 1);
    if (pq == NULL) {
      pq = newNode(rChild);
    } else
      push( & pq, rChild);
  }

}

void printPath(board * root) {
  if (root == NULL) return;
  else printPath(root -> parent);
  display(root -> data);
}
