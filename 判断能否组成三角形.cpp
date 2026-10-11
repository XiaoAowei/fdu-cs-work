#include<stdio.h> 
#include <stdbool.h>
bool is_triangle(int a, int b, int c) { 
if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    } else {
        return false;
    }
}


int main(void) {
    int x, y, z;

    scanf("%d %d %d", &x, &y, &z);

    if (is_triangle(x, y, z)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}
