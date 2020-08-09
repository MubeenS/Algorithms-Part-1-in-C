#include "minPQ.h"
 //input 3 0 1 3 4 2 5 7 8 6 
//input 3 8 1 3 4 0 2 7 6 5
void solve(int ** arr) {
  board * root = newBoard(arr, NULL, 0);
  Node * pq = newNode(root);
  int d=0;
  while (!isEmpty( & pq)) {
  	d++;
    board * peeked = peek( & pq);
    if (isGoal(peeked -> data)) {
      printf("\nPath");
      printPath(peeked);
      return;
    }
    //prints a dot to mind the user that code is running
    if(d>=2500) {
    	printf(". ");
    	d=0;
	} 
    pushNeighbors(peeked, pq);
    pop( & pq);
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
  printf("\n");
  solve(arr);
  return 0;
}
