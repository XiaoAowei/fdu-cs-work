#include <stdio.h>
int main (void)
{
	int N;
	int sum=0;
	int i;
	printf("Enter N:");
	scanf("%d",&N);
	for ( i=1;i<=N;i++)
	{
		sum=sum+i*i;
	}
	printf("%d\n",sum);
	return 0;
}
