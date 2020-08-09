#include "redBlackBST.h"
// input 0.6 0.5 0.4 0.3 0.8 0.6 0.1 0.4 0.6 0.9
bool contains(struct node **root,point p){
    if (*root == NULL){
       fprintf(stderr,"Tree is empty.");
       return;
    }
    else{
        struct node *y = NULL;
        struct node *x = (*root);
        // Follow standard BST insert steps to first insert the node
        while (x != NULL) {
            y = x;
            if (comparePoints(p,x->data) < 0)
                x = x->left;
            else if(comparePoints(p,x->data)>0)
                x = x->right;
            else
            return true;
        }
        return false;
    } 
}
int sizeOfTree(void) {
	return size;
}
void range(struct node *root,rect r){
    if (root == NULL)
        return;
    range(root->left,r);
    if(rectContains(r,root->data)) {
    printf("[%f,%f] \n", root->data.x,root->data.y);
	}
    range(root->right,r);
}
typedef struct minimum {
	point pt;
	int dist;
}minpoint;

void nearest(struct node *root,point p,minpoint *min) {
    if (root == NULL)
        return;
    nearest(root->left,p,min);
    if(distanceSquared(root->data,p) < min->dist) {
    	min->pt.x = root->data.x;
    	min->pt.y = root->data.y;
    	min->dist = distanceSquared(root->data,p);
	}
    nearest(root->right,p,min);
}

/* Driver program to test above function*/
int main() {
    struct node *root = NULL;
    int i;
    double x,y;
    point p;
    for ( i = 0; i < 5; ++i) {
    	scanf("%lf %lf",&x,&y);
    	p.x = x;
    	p.y = y;
    	insert(&root,p);
	}
	printf("\n");		
    printf("Inorder Traversal Is :\n");
    inorder(root);
    printf("\n");
    rect a;
    a.xmin=0.4;
    a.ymin=0.3;
    a.xmax=0.8;
    a.ymax=0.6;
    printf("Points inside rectangle:");
    range(root,a);
    p.x=0.0;
    p.y=0.0;
     printf("Point from tree closest to [%d,%d] is ",p.x,p.y);
    minpoint min;
    min.pt.x=99; min.pt.y=99;
    min.dist=99;
    nearest(root,p,&min);
    printf("[%f,%f]",min.pt.x,min.pt.y);
    return 0;
}
