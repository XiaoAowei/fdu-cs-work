#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Given n and an array `list` of n-1 integers, returns the smallest integer
//array 数组 value数值 NULL空 如果指针是NULL说明里面是空的 
// in the range [1, n] that does not appear in `list`.
//
// Notes:
//   - Values in `list` may repeat, so more than one value in [1, n] may be
//     missing. Since `list` has only n-1 entries, at least one value is
//     always missing, so the answer always exists for valid input.
//   - When n == 1, `list` has no elements and the answer is 1
//     (`list` may be NULL in this case).
//   - The function must not modify `list`.
//modify 修改 function 函数  input输入 ontput输出   invalid 无效的 
// Returns -1 if the input is invalid, i.e., if any of the following holds:
//   - n <= 0
//   - list == NULL while n > 1
//   - some element of `list` is outside the range [1, n]
int smallest_missing_element(int n, const int* list) {
  // TODO: implement this function
 
    if (n <= 0) return -1;
    if (n == 1) return 1;
    if (list == NULL) return -1;

    int* seen = (int*)calloc(n + 1, sizeof(int));
    if (seen == NULL) return -1;
/*第30行：向系统申请一段内存，用来当“记录本”。数组大小是 n + 1（因为下标要从 0 到 n）。
我们使用的是 calloc，它神奇的地方在于会自动把所有内存初始化为 0。int* 声明指针接收这块内存。
"我要一段能装 n+1 个整数的连续空间，内容全清成 0，把地址给我的指针 seen。"
· 第31行：如果申请失败（比如系统内存不够了），calloc 会返回 NULL，此时我们直接返回 -1，避免程序崩溃。*/
    int i;
    // 遍历 list 数组，做合法性检查
    for (i = 0; i < n - 1; i++) {
        if (list[i] < 1 || list[i] > n) {
            free(seen);
            return -1;
        }
        seen[list[i]] = 1;
        //如果合法，就把这个数字作为下标，在辅助数组 seen 里打上标记 1，表示“这个数字出现过”。
        //数字 list[i] 出现过了，在签到本的对应格子上打个勾（标 1）。"
//seen[x] = 1 的含义就是：数字 x 出现过。
//seen[x] 还是 0 的含义就是：数字 x 没出现过。

    }

    int result = -1;
    // 查找缺失值，必须遍历到 n
    for (i = 1; i <= n; i++) {
        if (seen[i] == 0) {
            result = i;
            break;
        }
    }

    free(seen);
    return result;
}


void TestCase1() {
  // Test Case 1: Basic case, a single missing value in the middle
  int n = 5;
  int list[4] = {1, 3, 4, 5};
  assert(smallest_missing_element(n, list) == 2);
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  // Test Case 2: The missing value is n itself
  int n = 6;
  int list[5] = {4, 1, 3, 2, 5};
  assert(smallest_missing_element(n, list) == 6);
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // Test Case 3: Duplicates present; multiple values are missing
  int n = 10;
  int list[9] = {8, 4, 6, 2, 9, 10, 7, 6, 8};  // missing 1, 3, 5
  assert(smallest_missing_element(n, list) == 1);
  printf("Passed %s\n", __func__);
}

void TestCase4() {
  // Test Case 4: Large input (performance test).
  // An O(n^2) solution will be noticeably slow here; aim for O(n).
  int n = 100000;
  int missing = 54321;
  int* list = malloc((n - 1) * sizeof(int));
  assert(list != NULL);

  int idx = 0;
  int i; 
  for ( i = 1; i <= n; i++) {
    if (i == missing) continue;
    list[idx++] = i;
  }

  // Fisher-Yates shuffle. Two rand() calls are combined because RAND_MAX
  // may be as small as 32767 on some platforms.
  srand(2026);
  for ( i = n - 2; i > 0; i--) {
    long r = (long)rand() * ((long)RAND_MAX + 1) + rand();
    int j = (int)(r % (i + 1));
    int tmp = list[i];
    list[i] = list[j];
    list[j] = tmp;
  }

  assert(smallest_missing_element(n, list) == missing);
  printf("Passed %s (large n=%d)\n", __func__, n);

  free(list);
}

void TestCase5() {
  // Test Case 5: Invalid n (zero and negative)
  int list[1] = {1};
  assert(smallest_missing_element(0, list) == -1);
  assert(smallest_missing_element(-3, list) == -1);
  printf("Passed %s\n", __func__);
}

void TestCase6() {
  // Test Case 6: NULL list with n > 1 is invalid
  assert(smallest_missing_element(5, NULL) == -1);
  printf("Passed %s\n", __func__);
}

void TestCase7() {
  // Test Case 7: Elements outside [1, n] are invalid
  int list_zero[4]     = {1, 0, 3, 4};    // contains 0
  int list_too_big[4]  = {1, 2, 6, 4};    // contains n + 1
  int list_negative[4] = {1, -2, 3, 4};   // contains a negative value
  assert(smallest_missing_element(5, list_zero) == -1);
  assert(smallest_missing_element(5, list_too_big) == -1);
  assert(smallest_missing_element(5, list_negative) == -1);
  printf("Passed %s\n", __func__);
}

void TestCase8() {
  // Test Case 8: n == 1, the list is empty, so the answer is 1
  assert(smallest_missing_element(1, NULL) == 1);
  int dummy[1] = {0};  // contents must not be read when n == 1
  assert(smallest_missing_element(1, dummy) == 1);
  printf("Passed %s\n", __func__);
}

void TestCase9() {
  // Test Case 9: All elements identical
  int list_ones[4]  = {1, 1, 1, 1};
  int list_fives[4] = {5, 5, 5, 5};
  assert(smallest_missing_element(5, list_ones) == 2);
  assert(smallest_missing_element(5, list_fives) == 1);
  printf("Passed %s\n", __func__);
}

void TestCase10() {
  // Test Case 10: The function must not modify the input list
  int n = 8;
  int list[7]     = {7, 3, 3, 8, 1, 6, 2};
  int original[7] = {7, 3, 3, 8, 1, 6, 2};
  assert(smallest_missing_element(n, list) == 4);
  assert(memcmp(list, original, sizeof(list)) == 0);
  printf("Passed %s\n", __func__);
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  TestCase4();
  TestCase5();
  TestCase6();
  TestCase7();
  TestCase8();
  TestCase9();
  TestCase10();
  printf("\nAll tests passed!\n");
  return 0;
}
