#include <stdio.h>
#include <assert.h>
#include <math.h>

// Solve the cubic equation三次方程 x^3 + c2*x^2 + c1*x + c0 = 0 with precision精度为 eps.
// Store the number of real roots实根的个数 in *cnt (possible values: 1, 2, or 3).
// Store the roots in sol[0], ..., sol[*cnt - 1], sorted in ascending order.按升序排列。
void solve_cubic_equ(double c2, double c1, double c0, double eps,
                     int *cnt, double *sol) {
    // void —— 返回类型

//solve_cubic —— 函数名

//(...) —— 参数列表

//{ ... } —— 函数体  eps	double	精度容差（epsilon），判断判别式是否接近 0

//sol	double *	指向数组，存根	输出
//cnt	int *	指向整数，存根个数	输出
  // TODO: Implement
  double x0=2.0;
  int iter;
  for(iter=0;iter<100;iter++)
  /*int iter;	声明一个整数变量，名字叫 iter，用来数"迭代了多少次"
iter = 0	初始化：从第 0 次开始
iter < 100	循环条件：只要还没到 100 次就继续
iter++	每循环一次，iter 加1*/ 
  {
  	double fx=x0*x0*x0+c2*x0*x0+c1*x0+c0;
  	double fdx=3*x0*x0+2*c2*x0+c1;
  	if(fabs(fdx)<eps)
  	//fabs求浮点数的绝对值
  	break;//如果导数的绝对值小于精度 eps，说明它太接近 0 了，不能安全地做除法，直接停止迭代。 
  	
  	double x1=x0-fx/fdx;
  	if(fabs(x1-x0)<eps)
  	{
  		x0=x1;
  		break;
	  }
	  x0=x1;
  }
  double r1=x0;
  *cnt=0;
  sol[(*cnt)++]=r1;
  
  double p=c2+r1;
  double q=c1+r1*p;
  
  double delta =p*p-4*q;
  if(delta>eps)
  {
  	double r2=(-p+sqrt(delta))/2.0;
  	double r3=(-p-sqrt(delta))/2.0;
  	sol[(*cnt)++]=r2;
  	sol[(*cnt)++]=r3;
  }
  else if(fabs(delta)<=eps)
  {
  	double r2=(-p)/2.0;
  	sol[(*cnt)++] =r2;
  }
  
  int i,j;
  int new_cnt=0;
  double temp_sol[3] ;
  for(i=0;i<*cnt;i++)
  {
  	int is_dup=0;
  	for(j=0;j<new_cnt;j++)
  	{
  		if(fabs(sol[i]-temp_sol[j])<eps*10)
  		{
  		 is_dup=1;
  		 break;
		  }
	  }
	  if(!is_dup) 
	  {
	  	temp_sol[new_cnt]=sol[i];
	  	new_cnt++;
	  }
  }
  
  for(i=0;i<new_cnt;i++)
  {
  	sol[i]=temp_sol[i];
  }
  *cnt=new_cnt;
  
  for(i=0;i<(*cnt)-1;i++)
  {
  	for(j=0;j<(*cnt)-1-i;j++)
  	{
  		if(sol[j]-sol[j+1]>eps)
  		{
  			double tmp=sol[j];
  			sol[j]=sol[j+1];
  			sol[j+1]=tmp;
		  }
	  }
  }
}

// Compares two double numbers x and y for equality within a specified tolerance eps.
// Returns 1 if the absolute difference between x and y is less than eps, 0 otherwise.
int compare_equal(double x, double y, double eps) {
  if (fabs(x - y) < eps) return 1;
  else return 0;
}

void TestCase1() {
  // Test Case 1: x^3 - 1 = 0, only one real root x = 1
  double eps = 1e-6;
  int cnt;
  double sol[3];
  solve_cubic_equ(0, 0, -1, eps, &cnt, sol);
  printf("Test Case 1: Expected 1 root, x = 1\n");
  printf("Number of roots: %d\n", cnt);
  int i;
  for ( i = 0; i < cnt; i++) {
      printf("Root %d: %.6f\n", i + 1, sol[i]);
  }
  assert(cnt == 1);
  assert(compare_equal(sol[0], 1.0, eps));
  printf("Passed TestCase1\n");
}

