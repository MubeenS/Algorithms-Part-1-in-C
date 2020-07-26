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
    float a=slope(p,p1),b=slope(p,p2);
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
int fastCollinearPoints(point *p,int size)  {
    point copy[size];
    int i,j;
    for(i=0;i<size;i++) copy[i]=p[i];
     int numOfSeg=0;
     qsort(copy,size,sizeof(point),compareTo);
     for(int k=0;k<size;k++){ //to display sorted copy as per points
        display(&copy[k]);
         printf("\t");
    }
    printf("\n");
    point slopeSorted[size-1];
    for(int i=0;i<size;i++) {
        int idx = 0;
		int numOfCollinear = 0;
		int lastIndex = 0;
		for(int k=0;k<size;k++) { //copy all except reference point
		    if(k==i)
		    continue;  printf("check for segfault\t");
		    slopeSorted[idx++] = copy[k];
		}
		qsort_r(slopeSorted,idx,sizeof(point),slopeOrder,&copy[i]);
		for (int k = 1; k < idx; k++) {
		    if(slope(&slopeSorted[i],&copy[k])!=slope(&slopeSorted[i],&copy[k-1])){
		        
		    }else {
		        numOfCollinear++;
		        lastIndex=k;
		        if (numOfCollinear > 1) {
						float slopeToLast = slope(&copy[i],&slopeSorted[lastIndex]);
						bool maxSegment = true;
						int numOfSame = 0;
						for (int n = 0; n < size; n++)
							if (slope(&copy[i],&slopeSorted[lastIndex]) == slope(&copy[i],&copy[n]))
								numOfSame++;
						for (int m = i-1; m >= 0; m--) {
							if (slope(&slopeSorted[lastIndex],&copy[m]) == slopeToLast)
								maxSegment = false;
						}
						
						if (maxSegment && numOfCollinear+2 == numOfSame+1) {
                            display(&copy[i]); printf("-> "); display(&slopeSorted[lastIndex]);	
						}
				}
		    }
		    if (k < idx && slope(&copy[i],&slopeSorted[k]) != slope(&copy[i],&slopeSorted[k+1])) 
					numOfCollinear = 0;
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
