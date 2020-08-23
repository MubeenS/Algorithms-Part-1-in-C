#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
/*input 8 10000 0 0 10000 3000 7000 7000 3000 3000 4000 20000 21000 14000 15000 6000 7000
output should be (10000,0)->(0,10000)  (3000,4000)->(20000,21000)
input 6 19000 10000 18000 10000 32000 10000 21000 10000 1234 5678 14000 10000
output should be (32000,10000)->(14000,10000)*/
#define inf INFINITY
typedef struct point_ {
    int x;
    int y;
    struct point_ *ref;
    
}point;

typedef struct lineSegment {
	point start;
	point end;
}lineSeg;

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

int slopeOrder(const void *p1_,const void *p2_) {
    point *p1 = (point *) p1_;
    point *p2 = (point *) p2_;
    float a=slope(p1,p1->ref);
    float b=slope(p2,p2->ref);
    if(a<b) return -1;
    else if(a>b) return 1;
    else return 0;
}
bool equalpoint(point p1,point p2) {
	if(p1.x==p2.x && p1.y==p2.y) return true;
	return false;
}
bool segsEqual(lineSeg *l1,lineSeg *l2 ) {
 if(equalpoint(l1->start,l2->start) && equalpoint(l1->end,l2->end)) return true ;
 if(equalpoint(l1->start,l2->end) && equalpoint(l1->end,l2->start)) return true ;
 return false;
}

void display (point *p){
	printf("(%d,%d)",p->x,p->y);
}
void FastCollinearPoints (point *p,int size) {
    qsort(p,size,sizeof(point),compareTo);
    int i;
    point copy[size-1];
    lineSeg l[size-1];
    int lindex=0;
    for(i=0;i<size;i++) {
        int idx=0,j,k;
        for(j=0;j<size;j++) {
            if(i==j) continue;
        copy[idx]=p[j];
        copy[idx].ref = &p[i];
         idx++;
        }
        //sorting as per slopes
        qsort(copy,idx,sizeof(point),slopeOrder);
    float currSlope=slope(&copy[0],&p[i]);
    int s=0,count=1; point sameSlope[idx];
    sameSlope[s++]=p[i];
        for(k=1;k<idx;k++) {
            if(slope(&copy[k],&p[i])==currSlope) {
              count++;
              if(k==1) {
			  count++;
		      }
		      sameSlope[s++]=copy[k-1];
              sameSlope[s++]=copy[k];
            }
            else {
            
                if(count>=3) { //collinearity of four points exists
                    qsort(sameSlope,s,sizeof(point),compareTo);
                    lineSeg temp;
                    temp.start= sameSlope[0]; 
                    temp.end = sameSlope[s-1];
                    int check=1; int m;
                    for(m=0;m<lindex;m++) {
                    	if(segsEqual(&l[m],&temp)==true) {
                    		check=0;
							break;
						}	
					} //forming line segment
					if(check==1 || lindex==0) {
						l[lindex].start = sameSlope[0];
						l[lindex].end  =  sameSlope[s-1];
							lindex++;
					}
                }
                count=1;
                currSlope=slope(&p[i],&copy[k]);
           }      
        }
    }
    int d;
    //displaying the distinct line segments
    for(d=0;d<lindex;d++) {
    	display(&l[d].start); printf("->"); display(&l[d].end);
    	printf("\n");
	}
}
int main () {
    
    int i,size;
    printf("Enter input \n");
    scanf("%d",&size);
    point p[size];
    for(i=0;i<size;i++) {
        scanf("%d %d",&p[i].x,&p[i].y);    
    }
    FastCollinearPoints(&p[0],size);
    return 0;
}
