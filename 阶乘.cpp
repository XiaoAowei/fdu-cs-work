#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	int x;
	x=1;
	int fact;
	fact=1;
	
	while(x<=n)
	{
		fact=fact*x;
		x++;
		
	}
	/*for(x=1,x<=n,x++);
	{fact*=x;
} */
	 
	printf("%d",fact);
	return 0; 
	
}
