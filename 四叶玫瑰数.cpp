
	#include <stdio.h>
	typedef struct {
    int x;
    int y;
} Point;
int point_equal(Point a, Point b) {
    return (a.x == b.x) && (a.y == b.y);
}

int main(void) {
    Point p1 = {1, 2};
    Point p2 = {1, 2};
    Point p3 = {1, 3};

    printf("%d\n", point_equal(p1, p2)); // 输出 1（相同）
    printf("%d\n", point_equal(p1, p3)); // 输出 0（不同）
    return 0;
}
/*	typedef struct {
    double x;
    double y;
} Point;
 
Point origin = {0, 0};
Point a = {3, 4};
printf("(%g, %g)\n", a.x, a.y);     
/*	int a,b,c,d;
	int num;
	
	for(num=1000;num<=9999;num++){
	
	   a=num/1000;
	   b=(num%1000)/100;
	   c=(num%100)/10;
	   d=num%10;
	   
	   if(num=a*a*a*a+b*b*b*b+c*c*c*c+d*d*d*d) 
	   {
	   	printf("%d\n",num);
	   }
}
return 0;
*/	   

