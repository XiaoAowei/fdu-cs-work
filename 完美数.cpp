bool checkPerfectNumber(int num) {
    if (num <= 1) {
        return false;
    }
    
    int sum = 1; // 1 是所有大于 1 的正整数的真因数
    
    // 只需要遍历到 sqrt(num) 即可，即 i * i <= num
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            // 如果 i 和 num/i 不相等，说明找到了两个不同的因数
            if (i * i != num) {
                sum += num / i;
            }
        }
    }
    
    return sum == num;
}
