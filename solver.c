#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//input 3 0 1 3 4 2 5 7 8 6 
//input 3 8 1 3 4 0 2 7 6 5
typedef struct node { 
    int **data; 
    // Lower values indicate higher priority 
    int priority;   
    struct node* next; 
  
} Node; 

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
Node* newNode(int **arr, int p) 
{ 
    Node* temp = (Node*)malloc(sizeof(Node)); 
    allocate_mem(&(temp->data));
    createTiles(temp->data,arr);
    temp->priority = p; 
    temp->next = NULL;   
    return temp; 
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
void neighbors(Node *curr) {
   int i,j,stop=0;
   int **temp;
   int **b=curr->data;
     allocate_mem(&temp);
   for(i=0;i<N;i++) {
     for(j=0;j<N;j++)
       if(b[i][j]==0) {
       	stop=1;break;
	   }
	   if(stop==1) break;
    }
	if(j-1>=0) {
		copy(temp,b);
		swap(temp,i,j-1,i,j);
		display(temp);	
	}
	if(i-1>=0) {
		copy(temp,b);
		swap(temp,i-1,j,i,j);
		display(temp);	
	}
	if(i+1<N) {
		copy(temp,b);
		swap(temp,i+1,j,i,j);
		display(temp);	
	}
	if(j+1<N) {
		copy(temp,b);
		swap(temp,i,j+1,i,j);
		display(temp);	
	}
	deallocate_mem(&temp);
}

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

int main () {
	int i,j,**arr;
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
	Node* tiles = newNode(arr,1);
    printf("Tiles :");
    display(tiles->data);
    printf("\n");
    createGoal();
    printf("Goal board :");
    display(goal);
    printf("Neighbors : ");
    neighbors(tiles);
    int **twin;
    allocate_mem(&twin);
    copy(twin,tiles->data);
    boardTwin(twin);
    printf("Twin Board:");
    display(twin);
	return 0;
}
