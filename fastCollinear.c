#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define inf INFINITY
typedef struct point_ {
    int x;
    int y;
    struct point_ ref;
}point;

int compareTo(const void *pp1,const void *pp2) {
    point *p1 = (point *) pp1;
    point *p2 = (point *) pp2;
    if(p1->y<p2->y) return -1;
    else if(p1->y==p2->y && p1->x<p2->x)
    return -1;
    else return 1;
}
float slope(point *p1,point *p2) {
    if(p2->y==p1->y && p2->x!=p1->x) return 0;//horizontal line segment
   else if(p2->x==p1->x && p2->y!=p1->y) return inf; //verticl line segment
   else if(p2->x==p1->x && p2->y==p1->y) return -inf;//point to itself
   else 
   return (p2->y-p1->y)/((float)(p2->x-p1->x));
}

int slopeOrder(const void *p1_,const void *p2_) {
    point *p1 = (point *) p1_;
    point *p2 = (point *) p2_;
    int a=slope(p,p1),b=slope(p,p2);
    if(a<b) return 1;
    else if(a>b) return -1;
    else return 0;
}

bool collinear(point *p,point *p1,point *p2,point *p3){
    if(slope(p,p1)==slope(p1,p2) && slope(p1,p2)==slope(p2,p3)) return true;
    else return false;
}
void display (point *p){
	printf("(%d, %d)",p->x,p->y);
}
int FastCollinearPoints (point *p,int n) {
    
    
}
int main () {
    
    int i,size;
    printf("Enter No.of points:\n");
    scanf("%d",&size);
    point p[size];
    for(i=0;i<size;i++) {
        printf("Enter x and y for point-%d :\n",i+1);
        scanf("%d %d",&p[i].x,&p[i].y);    
    }
    FastCollinearPoints(&p[0],size);
    return 0;
}
