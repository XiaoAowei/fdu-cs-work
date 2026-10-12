#include<stdio.h>
#include<math.h>
//#include<math.h>：引入数学库。因为代码中使用了 sqrt() 函数（求平方根），这个函数定义在 math.h 中。

void solve_quadratic_equation(double a, double b, double c, int *num, double 
*sol) { 
/*函数定义：定义了一个名为 solve_quadratic_equation 的函数，返回类型为 void（即不直接返回数值，而是通过指针修改外部变量）。

参数解释：

double a, double b, double c：方程的三个系数。

int *num：一个整型指针。用于将实数根的个数（0个、1个或2个）传回给主调函数。

double *sol：一个双精度浮点型指针，指向一个数组。用于将具体的根的值传回给主调函数。*/
 double delta=b*b-4*a*c;
 
 if(delta<0){
 	*num=0;
 	//*num=0;：通过指针将根的数量设为 0。
 }else if (delta==0){
 	*num=1;
 	sol[0]=-b/(2*a);
 	//计算这个唯一的根， ，并将其存入 sol 数组的第一个位置。
 }else{
 	*num=2;
 	double x1=(-b-sqrt(delta))/(2*a);
 	double x2=(-b+sqrt(delta))/(2*a);
 	
 	if(x1<x2){
 		sol[0]=x1;
 		sol[1]=x2;	
	 }
	 else {
	 		sol[0]=x2;
 		sol[1]=x1;
	 }
 }
 
}
