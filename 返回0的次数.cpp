#include <iostream>
using namespace std;

class Solution {
public:
    int numberOfSteps(int num) {
        int steps = 0;
        while (num > 0) {
            if (num % 2 == 0) {
                num /= 2;
            } else {
                num -= 1;
            }
            ++steps;
        }
        return steps;
    }
};

int main() {
    int t;
    cin >> t; // ²âÊÔÓÃÀý¸öÊý

    Solution s;
    while (t--) {
        int num;
        cin >> num;
        cout << s.numberOfSteps(num) << endl;
    }
      return 0;
}
