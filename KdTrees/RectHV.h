#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
typedef struct point2d {
	double x;
	double y;
}point;

double distanceSquared(point p,point q) {
	double dx= (p.x-q.x),dy=(p.y-q.y);
	return dx*dx+dy*dy;
}

double distancepoints(point p, point q) {
	return sqrt(distanceSquared(p,q));
}

bool equals(point p, point q) {
	return (p.x==q.x && p.y == q.y );
}
double comparePoints(point p,point q) {
	if(p.y != q.y) return p.y-q.y; //based on y
	return p.x-q.x;	//if y co-ordinates are equal break tie by 
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

//to check if two rectangles intersect
bool intersects(rect A,rect B) {
  return ((A.xmax >= B.xmin) && (A.ymax >= B.ymin) && (B.xmax>=A.xmin) && (B.ymax >= A.ymin)) ;
}

// distance squared from p to closest point on this axis-aligned rectangle

double distSquaredp2r(rect A, point p){
	double dx=0.0,dy=0.0;
	if(p.x< A.xmin) dx = p.x-A.xmin;
	else if(p.x>A.xmax) dx = p.x-A.xmax;
	if(p.y<A.ymin) dy= p.y-A.ymin;
	else if(p.y>A.ymax) dy= p.y-A.ymax;
	return dx*dx+dy*dy;
}
double dRectToPoint(rect A,point p) {
	return sqrt(distSquaredp2r(A,p));
}

bool rectEquals(rect A,rect B) {
    if(A.xmin!=B.xmin) return false;	
    if(A.xmax!=B.xmax) return false;
    if(A.ymin!=B.ymin) return false;
    if(A.ymax!=B.ymax) return false;
    return true;
}

void toString(rect A) {
	printf("[%d,%d] x [%d,%d]",A.xmin,A.ymin,A.xmax,A.ymax);
}

























