#include <stdio.h> 
#include <stdlib.h> 
#include "board4Q.h" 
// Node 
 
typedef struct node { 
    board *b; 
    // Lower values indicate higher priority 
    int priority; 
    struct node* next; 
  
} Node; 
  
// Function to Create A New Node 
Node* newNode(board *brd) 
{ 
    Node* temp = (Node*)malloc(sizeof(Node));
   //	board* tiles = newBoard(arr,manhattan(arr));
   	temp->b = newBoard(brd->data,manhattan(brd->data));
    temp->priority = brd->priority; 
    temp->next = NULL; 
    return temp; 
} 
  
// Return the value at head 
board* peek(Node** head) 
{ 
    return (*head)->b; 
} 

// Removes the element with the 
// highest priority form the list 
void pop(Node** head) 
{  
    Node* temp = *head; 
    (*head) = (*head)->next; 
    free(temp); 
} 
 
// Function to push according to priority 
void push(Node** head, board *d) 
{ 
    Node* start = (*head); 
    // Create new Node 
    Node* temp = newNode(d); 
  
    // Special Case: The head of list has lesser 
    // priority than new node. So insert new 
    // node before head node and change head node. 
    if ((*head)->priority > d->priority) { 
  
        // Insert New Node before head 
        temp->next = *head; 
        (*head) = temp; 
    } 
    else { 
  
        // Traverse the list and find a 
        // position to insert new node 
        while (start->next != NULL && 
               start->next->priority < d->priority) { 
            start = start->next; 
        } 
  
        // Either at the ends of the list 
        // or at required position 
        temp->next = start->next; 
        start->next = temp; 
    } 
} 
/*  
// Function to check is list is empty 
int isEmpty(Node** head) 
{ 
    return (*head) == NULL; 
} 
  */
// Driver code 
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
	display(tiles->data);
	printf("priority = %d",tiles->priority);
	Node *pq = newNode(tiles);
		printf("peek1");
	board *peeked = peek(&pq);
	display(peeked->data);
	//checking by inserting another
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
	board* tile = newBoard(arr,manhattan(arr));
	display(tile->data);
	printf("priority = %d",tile->priority);
	push(&pq,tile);
	pop(&pq);
	board *peekd = peek(&pq);
	printf("peek2");
	display(peekd->data);
	
    return 0; 
} 
