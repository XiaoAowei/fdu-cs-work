#include<stdio.h>

int main(void)
{
	int N;
	int i,j;
	printf("Enter the number of the rows:");
	scanf("%d",&N);
	
	for( i=0;i<N;i++)
	{
		for ( j=0;j<N;j++)
		{
			printf("*");
		}
//它在内层循环 { } 的外面，但在外层循环 { } 的里面。这意味着，每当内层循环把一整行的星号打印完了，就会执行一次换行。
		printf("\n");
	}
	return 0;
}
