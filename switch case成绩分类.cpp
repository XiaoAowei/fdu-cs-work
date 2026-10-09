#include<stdio.h>
int main()
{
	int grade;
	scanf("%d",&grade);
	grade=grade/10;
	
	switch (grade){
		case 10:
		case 9:
			printf("A\n");
			break;
		case 8:
			printf("B\n");
			break;
		default:
			printf("C\n");
			break;
	}
}
