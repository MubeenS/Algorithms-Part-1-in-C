#include <stdio.h> 
#include <stdlib.h> 
#include "minPQ.h"
//input 3 0 1 3 4 2 5 7 8 6 3 8 1 3 4 0 2 7 6 5
//input 3 8 1 3 4 0 2 7 6 5
//input 3 5 1 3 4 0 2 7 6 8
void pushNeighbors(board *brd,int numMoves,Node *pq) {
   int i,j,stop=0;
   int **temp,**t;
     allocate_mem(&temp);
   for(i=0;i<N;i++) {
     for(j=0;j<N;j++)
       if(brd->data[i][j]==0) {
       	stop=1;break;
	   }
	   if(stop==1) break;
    }
	if(j-1>=0) {
		copy(temp,brd->data);
		swap(temp,i,j-1,i,j);
		board *lChild = newBoard(temp,manhattan(temp)+numMoves);
		push(&pq,lChild);
		//display(temp);	
	}
	if(i-1>=0) {
		copy(temp,brd->data);
		swap(temp,i-1,j,i,j);
		board *uChild = newBoard(temp,manhattan(temp)+numMoves);
		push(&pq,uChild);
		//display(temp);	
	}
	if(i+1<N) {
		copy(temp,brd->data);
		swap(temp,i+1,j,i,j);
		board *dChild = newBoard(temp,manhattan(temp)+numMoves);
		push(&pq,dChild);
		//display(temp);	
	}
	if(j+1<N) {
		copy(temp,brd->data);
		swap(temp,i,j+1,i,j);
		board *rChild = newBoard(temp,manhattan(temp)+numMoves);
		push(&pq,rChild);
		//display(temp);	
	}
	//deallocate_mem(&temp);
}

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
	printf("Input tiles: \n");
    display(tiles->data);
    printf("\n");
    pushNeighbors(tiles,1,pq);
       while(!isEmpty(&pq)) {
    	board *peeked = peek(&pq);
    	printf("\n priority = %d",peeked->priority);
		display(peeked->data);
    	pop(&pq);
	}
    return 0; 
}
