#include <stdio.h>
#include <stdlib.h>

//input 3 0 1 3 4 2 5 7 8 6 

int **tiles;
int **goal;

void createTiles (int N,int **arr) {
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

void createGoal(int N) {
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
    		if(i==N-1 && j==N-1) {
    			goal[i][j] = 0;
			}
			else
    		goal[i][j] = filler++;
		}
	}
}
void display(int **tiles,int N) {
	int i,j;
	printf("%d\n",N);
	 for(i=0;i<N;i++) {
    	for(j=0;j<N;j++) {
    		if(tiles[i][j]==0) printf("  ");
    		else
    		printf("%d ",tiles[i][j]);
		}
		printf("\n");
	}
}
int hamming(int N) {
	int count=0,j,i;
	for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    		if(tiles[i][j]!=goal[i][j]) count++;
    		return count;
}
int main () {
	int i,j,N,**arr;
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
    createTiles(N,arr);
    createGoal(N);
    display(tiles,N);
    printf("\n");
    display(goal,N);
    int ham = hamming(N);
    printf("%d",ham);
	return 0;
}
