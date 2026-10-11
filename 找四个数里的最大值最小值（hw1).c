#include <stdio.h>
int main (void)
{
	int a,b,c,d;
	int max,min;
	printf("Enter 4 integers:");
	scanf("%d %d %d %d",&a,&b,&c,&d);
	
	max =a;
	if(b>max)max=b;
	if(c>max)max=c;
	if(d>max)max=d;
	
	min=a;
	if(b<min)min=b;
	if(c<min)min=c;
	if(d<min)min=d;
	
	printf("The minimum is %d\n",min);
	printf("The maximum is %d\n",max);
	return 0;
	
}
