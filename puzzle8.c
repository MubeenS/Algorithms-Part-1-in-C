#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//input 3 0 1 3 4 2 5 7 8 6 
//input 3 8 1 3 4 0 2 7 6 5

int **tiles;
int **goal;
int N;
void createTiles (int **arr) {
	int i,j;
	tiles = malloc( N*sizeof(int *) );        // N is the number of the rows
    if (tiles == NULL)
    return;
    for (i = 0 ; i < N ; i++)
     {
       tiles[i] = malloc( N*sizeof(int) );     // N is the number of the columns
       if (tiles[i] == NULL)
          return;
    }
    int filler=1;
    for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    		tiles[i][j] = arr[i][j];
}

void createGoal(void) {
	int i,j;
	goal = malloc( N*sizeof(int *) );        // N is the number of the rows
    if (goal == NULL)
    return;
    for (i = 0 ; i < N ; i++)
     {
       goal[i] = malloc( N*sizeof(int) );     // N is the number of the columns
       if (goal[i] == NULL)
          return;
    }
    int filler=1;
    for(i=0;i<N;i++) {
    	for(j=0;j<N;j++) {
    		if(i==N-1 && j==N-1) 
    			goal[i][j] = 0;
			else
    		goal[i][j] = filler++;
		}
	}
}
void display(int **t) {
	int i,j;
	printf("%d\n",N);
	 for(i=0;i<N;i++) {
    	for(j=0;j<N;j++) {
    		if(t[i][j]==0) printf("  ");
    		else
    		printf("%d ",t[i][j]);
		}
		printf("\n");
	}
}
int hamming(void) {
	int count=0,j,i;
	for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    		if(tiles[i][j]!=goal[i][j]) count++;
    		return count;
}

int manhattan(void) {
	int idx=0,hash[N*N],i,j,ir,jr,dist=0;
	for(i=0;i<N;i++) 
	 for(j=0;j<N;j++){
	 	if(i==N-1 && j==N-1) 
    			hash[idx] = 0;
			else
    		hash[idx++] = i*10+j;
	 }
	 for(i=0;i<N*N;i++)
	 printf("%d ",hash[i]);
	 
	 for(i=0;i<N;i++)
	  for(j=0;j<N;j++) {
	  	// taking out actual i and j that should be
	  	ir=hash[tiles[i][j]] / 10;
	  	jr=hash[tiles[i][j]] % 10;
	  	dist = dist + abs(ir-i) + abs(jr-j);
	  }
	  return dist;
}

bool isGoal(int **t) {
	int i,j;
	 for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    		if(t[i][j]!=goal[i][j]) return false;
	return true;
}

int main () {
	int i,j,**arr;
	printf("Enter dimension:");
	scanf("%d",&N);
	arr = malloc( N*sizeof(int *) );        // N is the number of the rows
	for (i = 0 ; i < N ; i++)
     arr[i] = malloc( N*sizeof(int) );     // N is the number of the columns
    
    for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) {
    		printf("a[%d][%d] =",i+1,j+1);
    		scanf("%d",&arr[i][j]);
		}
		printf("\n");
    createTiles(arr);
    createGoal();
    display(tiles);
    printf("\n");
    display(goal);
    int ham = hamming();
    printf("hamming = %d\n",ham);
    int man= manhattan();
    printf("Manhattan = %d\n",man);
    bool x= isGoal(tiles);
    printf("%s  ", x ? "true" : "false");
    x= isGoal(goal);
    printf("%s", x ? "true" : "false"); 
	return 0;
}
