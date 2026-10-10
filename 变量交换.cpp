#include <stdio.h>

void swap(int *pa, int *pb);
/*告诉编译器有一个叫 swap 的函数，接收两个整型指针 pa 和 pb，没有返回值（void）。
它出现在 main 函数之前，是为了让编译器在编译 main 时知道 swap 的格式。*/

int main(void)
{
    int a = 5;
    int b = 6;
    swap(&a, &b);
/*调用 swap 函数。注意这里传递的不是 a 和 b 的值，而是它们的内存地址（&a 和 &b）。这叫“传址调用”。*/
    printf("a=%d,b=%d\n", a,b);

    return 0;
}

void swap(int *pa, int *pb)
/*参数 pa 和 pb 是指针变量，它们分别接收了 main 函数中 a 和 b 的地址。此时，pa 指向 a，pb 指向 b。*/

{
    int t = *pa;
    *pa = *pb;
    *pb = t;
/*如果写成 void swap(int x, int y)，在函数内交换的只是 x 和 y 这两个形参的副本。
。当函数结束时，副本销毁，main 函数里的 a 和 b 根本不会改变。
想在函数内部修改外部变量的值，必须传递变量的地址（指针）。
swap 函数在自己的作用域内看不见 main 函数里的 a 和 b，它只认识传进来的指针 pa 和 pb。*/
}
