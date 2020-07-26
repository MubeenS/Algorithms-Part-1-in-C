#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define inf INFINITY
typedef struct point_ {
    int x;
    int y;
}point;

point* compareTo(point *p1,point *p2) {
    if(p1->y<p2->y) return p1;
    else if(p1->y==p2->y && p1->x<p2->x)
    return p1;
    else return p2;
}
float slope(point *p1,point *p2) {
    if(p2->y==p1->y && p2->x!=p1->x) return 0;//horizontal line segment
   else if(p2->x==p1->x && p2->y!=p1->y) return inf; //verticl line segment
   else if(p2->x==p1->x && p2->y==p1->y) return -inf;//point to itself
   else 
   return (p2->y-p1->y)/((float)(p2->x-p1->x));
}

int slopeOrder(const void *p11,const void *p22,void *arg) {
	point *p1 = (point *) p11;
	point *p2 = (point *) p22;
	point *p= (point*) p;
    int a=slope(p,p1),b=slope(p,p2);
    if(a<b) return -1;
    else if(a>b) return 1;
    else return 0;
}

bool collinear(point *p,point *p1,point *p2,point *p3){
    if(slope(p,p1)==slope(p1,p2) && slope(p1,p2)==slope(p2,p3)) return true;
    else return false;
}
void display (point *p){
	printf("(%d, %d)",p->x,p->y);
}
int fastCollinearPoints(point *p,int n) {
    point copy[n];
    int i,j;
    for(i=0;i<n;i++) copy[i]=p[i];
    for(i=0;i<n;i++){
    qsort_r(copy,n,sizeof(point),slopeOrder,&copy[0]);
       for(j=1;j<i+1;j++){//ignoring copy[0] as slope with itself will be smallest
           if(slope(&p[i],&copy[]))
       } 
    }
   
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

    return 0;
}
