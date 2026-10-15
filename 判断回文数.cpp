#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        
        string s = to_string(x);
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        return s == rev;
    }
};

int main() {
    Solution sol;
    int x;
    
    cout << "请输入一个整数: ";
    cin >> x;                        // ★ 从键盘读入一个数字
    
    if (sol.isPalindrome(x)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    
    return 0;
}