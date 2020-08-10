#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//sample input  0.6 0.5 0.4 0.3 0.8 0.6 0.1 0.4 0.6 0.9

typedef struct point2d {
	double x;
	double y;
}point;

double distanceSquared(point p,point q) {
	double dx= (p.x-q.x),dy=(p.y-q.y);
	return dx*dx+dy*dy;
}

double distance(point p, point q) {
	return sqrt(distanceSquared(p,q));
}

bool equals(point p, point q) {
	return (p.x==q.x && p.y == q.y );
}
typedef struct RectHV {
	double xmin;
	double ymin;
	double xmax;
	double ymax;
}rect;

//to check if p is within rectangle R
bool rectContains(rect R, point p) {
	return ((p.x >= R.xmin && p.x <=R.xmax) && (p.y >= R.ymin && p.y <= R.ymax));
}

#define VERTICAL 1
#define HORIZONTAL 0

typedef struct KdTree {
	point pt;
	int division;
	struct KdTree *left,*right;
}Node;
int size = 0;

//gives opposite direction of node
int getDivisionByNode(Node *node) {
	return node->division == VERTICAL ? HORIZONTAL : VERTICAL;
}
// Checks if point less than another point (depends on division)
bool isLessThan(point node,point root,int division) {
	return  division == VERTICAL ? node.x < root.x : node.y < root.y;
}

bool contains(Node *root,point p) {
	Node *current = root;
	while(true){
		if(current == NULL){
			return false;
		}
		if(equals(current->pt,p)){
			return true;
		}
		//if p is lesser we search left/bottom 
		//otherwise we search in right/top part
		if(isLessThan(p,current->pt,current->division)) {
		 current = current -> left;	
		}
		else {
			current = current->right;
		}
	}
}

//sets type of divison for node and inserts it
Node* insertNode(Node *node,Node *parent){
	if(parent==NULL){
		node->division = VERTICAL;
		return node;
	}
	//if new point is lesser than parent we go left/bottom 
	//otherwise we go right
	if(isLessThan(node->pt,parent->pt,parent->division)) {
		if(parent->left == NULL) {
			node->division = getDivisionByNode(parent);
			parent->left = node;
		}
		else {
			parent->left = insertNode(node,parent->left);
		}
    }
	else {
		if(parent->right == NULL) {
			node->division = getDivisionByNode(parent);
			parent->right = node;
		}
		else {
		    parent->right = insertNode(node,parent->right);
		}
	}
	return parent;
}

Node* insert(Node *root, point p){
	if(!contains(root,p)){
		Node *node = malloc(sizeof(*node)); //check here
		node->pt.x=p.x;
		node->pt.y=p.y;
		node->left=NULL; 
        node->right=NULL;
		root = insertNode(node,root);
		size++;
	}
	return root;
}
double **rangePoints;
int nthPoint =0;
 // Check range points inside of the node
void rangeNode(Node *node,rect r){
	if(node == NULL)
	return;
	
	if(rectContains(r,node->pt)) {
		rangePoints = realloc(rangePoints,(nthPoint+1)*sizeof(*rangePoints));
		rangePoints[nthPoint] = malloc(2*sizeof(*rangePoints[nthPoint]));
		rangePoints[nthPoint][0] = node->pt.x;
		rangePoints[nthPoint][1] = node->pt.y;
		nthPoint++;
	}
	
	if(node->division == VERTICAL) {
		if(node->pt.x > r.xmin) {
			rangeNode(node->left,r);
		}
		if(node->pt.x <= r.xmax) {
			rangeNode(node->right,r);
		}
	}
	else {
		if(node->pt.x > r.xmin) {
			rangeNode(node->left,r);
		}
		if(node->pt.x <= r.xmax) {
			rangeNode(node->right,r);
		}	
	}
}

void range(Node *root,rect r){
	if(root == NULL){
		printf("Tree is empty");
		return;
	}
	rangeNode(root,r);
}

Node* nearestNode(point p,Node *node,Node* nearest){
	if(node == NULL) 
	return nearest;
	//if node point is closer to p than
	//so far obtained nearest update nearest
	if(distance(p,node->pt) < distance(p,nearest->pt)){
	 nearest = node ;
    }
    //checks if there is closer point in left sub-tree
    Node *nodeLeft = nearestNode(p,node->left,nearest);
    if(distance(nodeLeft->pt,p) < distance(nearest->pt,p)){
    	nearest=nodeLeft;
	}
	//checks if there is closer point in right sub-tree
	Node *nodeRight = nearestNode(p,node->right,nearest);
	if(distance(nodeRight->pt,p) < distance(nearest->pt,p)){
       nearest = nodeRight;	
	}
	return nearest;
}
point nearest(Node *root,point p){
	if(root == NULL){
		fprintf(stderr,"Tree is empty");
		return ;
	}
   Node *n = nearestNode(p,root,root);
   return n->pt;
}
//inorder taversal
void displayTree(Node *root) {
	if(root == NULL)
	return;
	displayTree(root->left);
	printf("[%f,%f]",root->pt.x,root->pt.y);
	displayTree(root->right);
}
//driver code to test the above functions
int main() {
    Node *root = NULL;
    int i;
    double x,y;
    point p;
    for ( i = 0; i < 5; ++i) {
    	scanf("%lf %lf",&x,&y);
    	p.x = x;
    	p.y = y;
    	root = insert(root,p);
	}
	printf("\nTree:");
	displayTree(root);
    rect a;
    a.xmin=0.4;
    a.ymin=0.3;
    a.xmax=0.8;
    a.ymax=0.6;
    printf("\nPoints inside rectangle:");
    rangePoints = malloc(sizeof(rangePoints));
    range(root,a);
    for(i=0;i<nthPoint;i++){
    printf("[%f,%f] ",rangePoints[i][0],rangePoints[i][1]);	
	}
    p.x = 0;
    p.y = 0;
    point q = nearest(root,p);
    printf("\nNearest point is [%f,%f]",q.x,q.y); 
    return 0;
}
