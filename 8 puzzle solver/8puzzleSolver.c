#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 //Sample input 3 0 1 3 4 2 5 7 8 6 
//Sample input 3 8 1 3 4 0 2 7 6 5 
//no solution input 3 1 2 3 4 5 6 8 7 0
int ** goal;
int N;

void allocate_mem(int ** * arr) {
  * arr = (int ** ) malloc(N * sizeof(int * ));
  int i;
  for (i = 0; i < N; i++)
    ( * arr)[i] = (int * ) malloc(N * sizeof(int));
}

void deallocate_mem(int ** * arr) {
  int i, N;
  for (i = 0; i < N; i++)
    free(( * arr)[i]);
  free( * arr);
}

void createTiles(int ** tiles, int ** arr) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      tiles[i][j] = arr[i][j];
}

void createGoal(void) {
  int i, j;
  allocate_mem( & goal);
  int filler = 1;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (i == N - 1 && j == N - 1)
        goal[i][j] = 0;
      else
        goal[i][j] = filler++;
    }
  }
}

void display(int ** t) {
  int i, j;
  printf("\n%d\n", N);
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (t[i][j] == 0) printf("  ");
      else
        printf("%d ", t[i][j]);
    }
    printf("\n");
  }
}

int hamming(int ** tiles) {
  int count = 0, j, i;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      if (tiles[i][j] == 0) continue;
      if (tiles[i][j] != goal[i][j]) count++;
    }
  return count;
}

bool equals(int ** p, int ** q) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      if (p[i][j] != q[i][j]) return false;
  return true;
}

bool isGoal(int ** t) {
  return equals(t,goal);
}
void swap(int ** surface, int x1, int y1, int x2, int y2) {
  int temp = surface[x1][y1];
  surface[x1][y1] = surface[x2][y2];
  surface[x2][y2] = temp;
}

void copy(int ** toRet, int ** origin) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      toRet[i][j] = origin[i][j];
}

//finds twin of board by exchanging any two blocks
void boardTwin(int ** toRet ) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N - 1; j++) {
      if (toRet[i][j] != 0 && toRet[i][j + 1] != 0) {
        swap(toRet, i, j, i, j + 1);
      }
    }
  }
}

typedef struct board_ {
  int ** data;
  // Lower values indicate higher priority 
  int cost;
  int level;
  struct board_ * parent;
}
board;

board * newBoard(int ** arr, board * parent, int level) {
  board * temp = (board * ) malloc(sizeof(board));
  allocate_mem( & (temp -> data));
  createTiles(temp -> data, arr);
  temp -> cost = hamming(arr);
  temp -> level = level;
  temp -> parent = parent;
  return temp;
}

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
    } 
	else if(brd->parent == NULL)
      push( & pq, dChild);
      //Avoid pushing parent as a child again
    else if(!equals(brd->parent->data,dChild->data)) {
     push( & pq, dChild);	
	}
  }
  if (j - 1 >= 0) {
    copy(temp, brd -> data);
    swap(temp, i, j - 1, i, j);
    board * lChild = newBoard(temp, brd, brd -> level + 1);
    if (pq == NULL) {
      pq = newNode(lChild);
    } 
	else if(brd->parent == NULL)
      push( & pq, lChild);
      //Avoid pushing parent as a child again
    else if(!equals(brd->parent->data,lChild->data)) {
     push( & pq, lChild);	
	}  
  }
  if (i - 1 >= 0) {
    copy(temp, brd -> data);
    swap(temp, i - 1, j, i, j);
    board * uChild = newBoard(temp, brd, brd -> level + 1);
    if (pq == NULL) {
      pq = newNode(uChild);
    } 
   	else if(brd->parent == NULL)
      push( & pq, uChild);
      //Avoid pushing parent as a child again
    else if(!equals(brd->parent->data,uChild->data)) {
     push( & pq, uChild);	
	}  
  }

  if (j + 1 < N) {
    copy(temp, brd -> data);
    swap(temp, i, j + 1, i, j);
    board * rChild = newBoard(temp, brd, brd -> level + 1);
    if (pq == NULL) {
      pq = newNode(rChild);
    }	
    else if(brd->parent == NULL)
      push( & pq, rChild);
      //Avoid pushing parent as a child again
    else if(!equals(brd->parent->data,rChild->data)) {
     push( & pq, rChild);	
	}  
  }

}

void printPath(board * root) {
  if (root == NULL) return;
  else printPath(root -> parent);
  display(root -> data);
}

void solve(int ** arr) {
  board * root = newBoard(arr, NULL, 0);
  Node * pq = newNode(root);
  //Creating a twin array to solve
   int **twinArr;
   int i;
   twinArr = malloc(N * sizeof(int * )); // N is the number of the rows
     for (i = 0; i < N; i++)
       twinArr[i] = malloc(N * sizeof(int)); // N is the number of the columns
       copy(twinArr,arr);
	   boardTwin(twinArr);
    board * rootTwin = newBoard(twinArr, NULL, 0);
    Node * pqTwin = newNode(rootTwin);
  //if twin is solved,no solution for main
  while (!isEmpty( & pq) || !isEmpty(&pqTwin)) {
    board * peeked = peek( & pq);
    board * peekedTwin = peek(& pqTwin);
    if (isGoal(peeked -> data)) {
      printf("\nPath");
      printPath(peeked);
      return;
    }
    //Checks if twin is solved
    if (isGoal(peekedTwin -> data)) {
      printf("\n No solution exists for entered board.");
      return;
    }
    pushNeighbors(peeked, pq);
    pop( & pq);
    //push peekedTwin neighbors
    pushNeighbors(peekedTwin, pqTwin);
    //pop minimum from twin queue
    pop( & pqTwin);
  }
}

int main() {
  // Create a Priority Queue 
  int i, j, ** arr;
  printf("Enter input:");
  scanf("%d", & N);
  createGoal();
  arr = malloc(N * sizeof(int * )); // N is the number of the rows
  for (i = 0; i < N; i++)
    arr[i] = malloc(N * sizeof(int)); // N is the number of the columns
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      scanf("%d", & arr[i][j]);
    }
  solve(arr);
  return 0;
}
