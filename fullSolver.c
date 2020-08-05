#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//input 3 0 1 3 4 2 5 7 8 6 
//input 3 8 1 3 4 0 2 7 6 5
//input 3 5 1 3 4 0 2 7 6 8
int **goal;
int N;
void allocate_mem(int ***arr) {
  *arr = (int**)malloc(N*sizeof(int*));
  int i;
  for(i=0; i<N; i++)
    (*arr)[i] = (int*)malloc(N*sizeof(int));
} 
void deallocate_mem(int*** arr){
     int i,N;
    for (i = 0; i < N; i++)
        free((*arr)[i]);
    free(*arr); 
}
void createTiles (int **tiles,int **arr) {
	int i,j;
     for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    		tiles[i][j] = arr[i][j];
}

void createGoal(void) {
	int i,j;
allocate_mem(&goal);
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
	printf("\n%d\n",N);
	 for(i=0;i<N;i++) {
    	for(j=0;j<N;j++) {
    		if(t[i][j]==0) printf("  ");
    		else
    		printf("%d ",t[i][j]);
		}
		printf("\n");
	}
}
int hamming(int **tiles) {
	int count=0,j,i;
	for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) {
            if(tiles[i][j]==0) continue;
    		if(tiles[i][j]!=goal[i][j]) count++;
        }
    		return count;
}

int manhattan(int **tiles) {
	int i,j,dist=0,ir,jr;	 
	 for(i=0;i<N;i++)
	  for(j=0;j<N;j++) {
	  	if(tiles[i][j]==0) continue;
	  	ir=(tiles[i][j]-1) / N;
	  	jr=(tiles[i][j]-1) % N;
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

bool equals(int **p,int **q) {
		int i,j;
	 for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    		if(p[i][j]!=q[i][j]) return false;
	return true;	
}
void swap(int **surface, int x1, int y1, int x2, int y2) {
  int temp = surface[x1][y1];
    surface[x1][y1] = surface[x2][y2];
    surface[x2][y2] = temp;
} 
void copy(int **toRet,int **origin) {
		int i,j;
	 for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    	toRet[i][j]=origin[i][j];
}
//finds twin of board by exchanging any two blocks
void boardTwin(int **toRet) {
	int i,j;
	   for (i = 0; i < N; i++) {
            for (j = 0; j < N-1; j++) {
                if (toRet[i][j] != 0 && toRet[i][j+1] != 0) {
                    swap(toRet,i, j, i, j+1);
                }
            }
        }		
}
typedef struct board_ { 
    int **data; 
    // Lower values indicate higher priority 
    int priority;   
    struct board_* parent; 
  
}board; 

board* newBoard(int **arr, int p) 
{ 
    board* temp = (board*)malloc(sizeof(board)); 
    allocate_mem(&(temp->data));
    createTiles(temp->data,arr);
    temp->priority = p; 
    temp->parent = NULL;   
    return temp; 
} 
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
 
// Function to check is list is empty 
int isEmpty(Node** head) 
{ 
    return (*head) == NULL; 
} 

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
    printf("\n foundspace for pushing");
	if(j-1>=0) {
			printf("pushd");
		copy(temp,brd->data);
			printf("copyd");
		swap(temp,i,j-1,i,j);
			printf("swapd");
		board *lChild = newBoard(temp,manhattan(temp)+numMoves);
		lChild->parent = brd;
		push(&pq,lChild);
		display(lChild->data);	
	}
	if(i-1>=0) {
		copy(temp,brd->data);
		swap(temp,i-1,j,i,j);
		board *uChild = newBoard(temp,manhattan(temp)+numMoves);
		uChild->parent = brd;
		push(&pq,uChild);
		//display(temp);	
	}
	if(i+1<N) {
		copy(temp,brd->data);
		swap(temp,i+1,j,i,j);
		board *dChild = newBoard(temp,manhattan(temp)+numMoves);
		dChild->parent = brd;
		push(&pq,dChild);
		//display(temp);	
	}
	if(j+1<N) {
		copy(temp,brd->data);
		swap(temp,i,j+1,i,j);
		board *rChild = newBoard(temp,manhattan(temp)+numMoves);
	    rChild->parent = brd;
		push(&pq,rChild);
		//display(temp);	
	}
	//deallocate_mem(&temp);
}
void printPath(board * brd) {
	if(brd == NULL) return;
	printPath(brd->parent);
	display(brd->data);
	
}
void solve(int **arr) {
	int numMoves = 0;
	board *root = newBoard(arr,manhattan(arr)); //creating board for root
	Node *pq = newNode(root); //pushed root into pq
	//loop finds live node
	//pushes its neighbors into pq
	//finally deletes live from pq
	printf("before while");
	while(!isEmpty(&pq)) {
		printf("\nEntered while");
		board *min = peek(&pq); //gives highest priority i.e, least number
		pop(&pq); //deleted the top node
		if(isGoal(min->data)) {
			printf("Goaled sorry");
			printPath(min);
			return;
		}
		numMoves=numMoves+1;
	//push neighbors into queue
	pushNeighbors(min,numMoves,pq);	
	}
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
	createGoal();
	solve(arr);
    return 0; 
}
