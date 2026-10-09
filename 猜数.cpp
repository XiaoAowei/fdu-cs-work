#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	srand(time(0));
	int number;
	number=rand()%100+1;
	int count;
	int a;
	count=0;
	a=0;
do{
	scanf("%d",&a);
	count++;
	if(a>number){
	printf("你输出的数大了\n");
	}else if (a<number){
		printf("你输出的数小了\n");
	}
}while(a!=number);
printf("你用了%d次就猜到了\n",count);
return 0;
}
