#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Dynamically allocate 动态分配an int array of length n,一个长度为 n 的 int 数组
// initialize every element to `value`, and将每个元素初始化为 value
// return a pointer to the allocated array.返回指向所分配数组的指针
int* create_and_fill_array(int n, int value) {
  // Write your code here.
  // Make sure the pointer you return is NULL or is valid.
  	if(n<=0)
  	{
  		return NULL;
	  }
	  //如果 n <= 0，说明请求的数组长度不合法（0 或负数）。

//直接返回 NULL，表示"分配失败/无效请求"。 
	int *arr=(int *)malloc(n*sizeof(int));
	//int *arr	声明一个指向 int 的指针 arr
//malloc(...)	在堆上分配内存，返回 void*
//n*sizeof(int)	需要的字节数 = 元素个数 × 每个 int 的大小
//(int *)	强制类型转换：把 void* 转成 int*
	int i;
	if(arr==NULL)
	{
		return NULL;
	}
	//int i; 声明循环计数器（C89 风格：变量声明放块开头）。

//如果 malloc 返回 NULL（内存不足），直接返回 NULL。

//这是必须的检查：不对 NULL 解引用，否则程序崩溃
	for (i=0;i<n;i++)
	{
		arr[i] =value;
	}
	return arr;
  
}
