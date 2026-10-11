#include<stdio.h>

 int sum_of_squares(int a,int b,int c)
 /*向 C 语言“注册”一个全新的工具（函数），并规定这个工具怎么用、需要什么材料、产出什么结果。
  int 表示这个“工具”干完活之后，会交出一个整数（int）。
  sum_of_squares —— 工具的名字
 这是咱们给这个自定义函数起的名字。
  (int a, int b, int c) —— 进料口（参数/形参）
 这括号里的内容，规定了这台“机器”运转需要投入几个材料，以及材料的数据类型。
 int a, int b, int c 意思是：这台机器需要你扔进去三个整数。
 我定义了一个名叫 sum_of_squares 的函数，它最终会返回一个整数。
 但是，想要启动它，你必须给它提供三个整数。在它的内部，这三个整数暂时分别叫做 a、b 和 c。”
*/
{
	// 函数体开始。
	return a*a+b*b+c*c;
}
//自定义函数结束
int main()
//程序执行的起点。
{
	int x,y,z;
	scanf("%d %d %d",&x,&y,&z);
	int result=sum_of_squares(x,y,z);
	printf("%d\n",result);
	return 0;
}
