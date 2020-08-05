#include <stdio.h> 
#include <stdlib.h> 
#include "minPQ.h"
//input 3 0 1 3 4 2 5 7 8 6 3 8 1 3 4 0 2 7 6 5
//input 3 8 1 3 4 0 2 7 6 5
//input 3 5 1 3 4 0 2 7 6 8

int main() 
{ 
    // Create a Priority Queue 
int i,j,**arr,numMoves=0;
	printf("Enter input:");
	scanf("%d",&N);
	arr = malloc( N*sizeof(int *) );        // N is the number of the rows
	for (i = 0 ; i < N ; i++)
     arr[i] = malloc( N*sizeof(int) );     // N is the number of the columns
    
    for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) {
    		scanf("%d",&arr[i][j]);
		}
		printf("\n");
	board* tiles = newBoard(arr,manhattan(arr));	
	Node *pq = newNode(tiles);
	//checking by inserting another
	scanf("%d",&N);
	arr = malloc( N*sizeof(int *) );        // N is the number of the rows
	for (i = 0 ; i < N ; i++)
     arr[i] = malloc( N*sizeof(int) );     // N is the number of the columns  
    for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) {
    		scanf("%d",&arr[i][j]);
		}
		printf("\n");
	board* tile = newBoard(arr,manhattan(arr));
	push(&pq,tile);
    while(!isEmpty(&pq)) {
    	printf("isEmpty = %d",isEmpty(&pq));
    	board *peeked = peek(&pq);
    	display(peeked->data);
    	printf("priority = %d",peeked->priority);
    	pop(&pq);
	}
	printf("isEmpty = %d",isEmpty(&pq));
    return 0; 
}
