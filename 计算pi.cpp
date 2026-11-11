#include <stdio.h>
#include <math.h>

#define EPS 1e-6

int main(void)
{
    double sum = 0.0;
    double term = 1.0;   // 当前项
    int sign = 1;        // 符号：+1, -1, ...
    int d = 1;           // 分母：1, 3, 5, ...

    while (fabs(term) >= EPS) {
        sum += term;
        d += 2;
        sign = -sign;
        term = (double)sign / d;
    }
    printf("pi = %.8f\n", 4 * sum);
    return 0;
}

