#include<stdio.h>
#include <stdbool.h>
// 引入布尔类型库。这是重点！ 在标准 C 语言里，原生是没有 bool（布尔）、true（真）、false（假）这三个关键字的。
//必须加上这个头文件，编译器才认识它们。如果没有这一行，第3行的 bool 就会报错。
bool is_prime(int n)
// 定义了一个名叫 is_prime 的函数。
// 返回类型是 bool（布尔值），也就是说它算完后只会给出 true（是素数）或 false（不是素数）两种结果。
// 形参：需要一个整数 n（等待主函数喂给它数字）。

{
	int i;
	
	if(n<=1){
		 return false;
	}
	     
	for( i=2;i*i<=n;i++) {
		if(n%i==0){
			return false;
		}
		//如果 n 是合数（比如输入 9）：代码会在第13行执行 return false;。
		//一旦执行这一行，整个 is_prime 函数瞬间结束！ 它连第16行的影子都看不到，就会直接带着 false 回到主函数。
	}
	return true;
		     
}
//自定义函数结束
// 主函数开始。

 int main()
{
	int num;
	scanf("%d",&num);
	
	if(is_prime(num)){
		//is_prime(num) 最终会变成一个 true (在底层其实就是数字1) 或者 false (底层是0)。

// 如果结果算出来是 true（非0），if 就认为条件成立。
//· 如果结果算出来是 false（0），if 就认为条件不成立。

		printf("true\n",num);
		
	}else{
		printf("false\n",num);
	}
	
   	  return 0;
}
