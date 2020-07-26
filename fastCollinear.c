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
   else if(p2->x==p1->x && p2->y!=p1->y) return inf; //vertical line segment
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
int fastCollinearPoints(point *p,int n)  {
    point copy[n];
    int i,j;
    for(i=0;i<n;i++) copy[i]=p[i];
     int numOfSeg=0;
     qsort(copy,n,sizeof(point),compareTo);
     /*for(int k=0;k<n;k++){ //to display sorted copy as per points
        printf("\t");
        display(&copy[k]);
    }
    printf("\n");*/
    for(i=0;i<n;i++){
    qsort_r(copy,n,sizeof(point),slopeOrder,&copy[i]);
    
    float currSlope=slope(&p[i],&copy[1]);
    float prevSlope=currSlope;
    int count=0;
       for(j=1;j<n-i;j++){//ignoring copy[0] as slope with itself will be smallest
           if(slope(&p[i],&copy[j])==currSlope){
               count++;
           }
           //counting from new set of slopes
           else { 
           //to display line segment that has more than 3 collinear points
               if(count>=3) { 
                   display(&p[i]); printf("-> "); display(&copy[j-1]); 
                   printf("\n");
               }
                count=0;
               
               currSlope = slope(&p[i],&copy[j]);
               prevSlope = currSlope;
           }
           if(count>=3) {
              if(numOfSeg==0) numOfSeg++; //for first set of line segments
              if(prevSlope!=currSlope) numOfSeg;  //for other sets of collinears
           }
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
    fastCollinearPoints(p,size);

    return 0;
}
