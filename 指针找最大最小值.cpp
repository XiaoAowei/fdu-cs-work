#include <stdio.h>

void minmax(int a[], int len, int *max, int *min); // 声明
// 接收一个整型数组 a，数组长度 len，以及两个整型指针 max 和 min。
int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9,12,13,14,16,17,21,23,55,};
    int min,max;
    minmax(a, sizeof(a)/sizeof(a[0]), &min, &max);
    //a：传递数组首地址。
//sizeof(a)/sizeof(a[0])：计算数组长度。
//&min, &max：传递 min 和 max 的地址（指针）
    printf("min=%d,max=%d\n", min, max);

    return 0;
}

void minmax(int a[], int len, int *min, int *max) // 定义
{
    int i;
    *min = *max=a[0];
    for ( i=1; i<len; i++ ) {
        if ( a[i] < *min ) {
            *min = a[i];
        }
        if ( a[i] > *max ) {
            *max = a[i];
        }
    }
}
