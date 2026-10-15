#include<stdio.h>
int main ()
{
	char a='F';
	int f=123;
	
	char *pa=&a;
	int *pb=&f;
	
	printf("a=%c\n",*pa);
	printf("f=%d\n",*pb);
	
	*pa='C';
	*pb+=1;
		printf("a=%c\n",*pa);
	printf("f=%d\n",*pb);
	
	
	
	
	return 0;
}
