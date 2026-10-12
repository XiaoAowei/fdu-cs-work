#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// The following library functions are NOT allowed in my_strlen.
// Any call to them inside my_strlen will cause a compile error.
#define strlen  DO_NOT_USE_strlen
#define strnlen DO_NOT_USE_strnlen
#define strchr  DO_NOT_USE_strchr
#define strrchr DO_NOT_USE_strrchr
#define memchr  DO_NOT_USE_memchr

// Returns the length of the C string `s`, i.e., the number of characters
// before the terminating null character '\0'. The null character itself
// is not counted.
//the terminating null character '\0'	终止空字符 '\0'
//空字符本身is not counted	不被计算在内
//compile 编译 string 字符串 
// 单引号 'a' → 一个字符（char） 双引号 "a" → 一个字符串（string）
//char str[] = "hello";
/*内存里是：

text
下标:   0    1    2    3    4    5
字符:  'h'  'e'  'l'  'l'  'o'  '\0'
                                  ↑
                          终止空字符，不算进去
那么"\0 之前的字符数量" = h e l l o = 5 个。

所以 strlen("hello") 返回 5，而不是 6——结尾的 \0 不计入长度。

这句话是在描述什么
它在描述 strlen 函数的返回值含义：

strlen 返回的是字符串中 \0 之前的字符个数，不包含 \0 本身。

一句话总结
长度 = 从开头数到 \0 前面为止的字符个数，\0 自己不算。

这也是为什么初学者常踩的坑："hello" 有 5 个字符，但它在内存里实际占 6 个字节（多出来的那个字节就是 \0）。长度和占用空间是两回事。

*/




// Notes:
//   - The length is measured in bytes (chars). A multi-byte UTF-8
//     character such as a Chinese character counts as several bytes.
//长度是按字节（char）来计算的。像中文这种多字节的 UTF-8 字符，会被算作好几个字节。
//   - The function must not modify the string.
//该函数不得修改这个字符串。
//   - Do not call strlen or any other library function; count the
//     characters yourself with a loop.
//不要调用 strlen 或任何其他库函数；请自己用循环来数字符
// Returns -1 if s is NULL.
int my_strlen(const char* s) {
  // TODO: implement this function
    // 1. 处理题目要求的边界情况：如果是空指针，直接返回 -1
    if (s == NULL) {
        return -1;
    }

    // 2. 声明一个计数器
    int count = 0;

    // 3. 循环遍历字符串
    // *s 代表当前指针指向的字符，不等于 '\0' 就说明还没到字符串末尾
    while (*s != '\0') {
    	/*0	数字零（int）	整数 0
'0'	字符零（char）	字符 '0'，ASCII 值是 48
'\0'	转义字符：空字符	字符 NUL，ASCII 值是 0
"\0"	字符串	里面含一个 \0，再加一个结尾 \0*/
        count++;  // 计数器加 1
        s++;      // 指针向后移动一位，指向下一个字符
        //s++;指针往后挪一格，指向下一个字符。

//注意：s++ 改的是指针本身（让它指向别处），不是改字符串内容，
//所以没有违反 const。const char* s 限制的是"不能改 *s（指向的内容）"，但"改 s（指针本身）"是允许的。
    }

    // 4. 返回统计出来的长度
    return count;
}


// Library functions are allowed again in the test code below.
#undef strlen
#undef strnlen
#undef strchr
#undef strrchr
#undef memchr

void TestCase1() {
  // Test Case 1: A simple word
  assert(my_strlen("hello") == 5);
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  // Test Case 2: The empty string has length 0
  assert(my_strlen("") == 0);
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // Test Case 3: A single character
  assert(my_strlen("a") == 1);
  assert(my_strlen(" ") == 1);
  printf("Passed %s\n", __func__);
}

void TestCase4() {
  // Test Case 4: Spaces, digits, and punctuation are ordinary characters
  assert(my_strlen("Hello, World!") == 13);
  assert(my_strlen("  2 + 2 = 4  ") == 13);
  printf("Passed %s\n", __func__);
}

void TestCase5() {
  // Test Case 5: Escape sequences each count as ONE character
  assert(my_strlen("\n") == 1);
  assert(my_strlen("a\tb\nc") == 5);
  assert(my_strlen("\\") == 1);  // a single backslash
  printf("Passed %s\n", __func__);
}

void TestCase6() {
  // Test Case 6: The string ends at the FIRST null character
  assert(my_strlen("abc\0def") == 3);
  char buf[10] = {'x', 'y', '\0', 'z', 'z', 'z', 'z', 'z', 'z', '\0'};
  assert(my_strlen(buf) == 2);
  printf("Passed %s\n", __func__);
}

void TestCase7() {
  // Test Case 7: A pointer into the middle of a string
  const char* s = "programming";
  assert(my_strlen(s + 3) == 8);   // "gramming"
  assert(my_strlen(s + 11) == 0);  // points at the '\0'
  printf("Passed %s\n", __func__);
}

void TestCase8() {
  // Test Case 8: A string stored in a char array that is larger than needed
  char buf[100] = "C language";
  assert(my_strlen(buf) == 10);
  buf[1] = '\0';  // truncate the string to "C"
  assert(my_strlen(buf) == 1);
  printf("Passed %s\n", __func__);
}

void TestCase9() {
  // Test Case 9: Multi-byte UTF-8 characters are counted in bytes.
  // "\xe4\xbd\xa0\xe5\xa5\xbd" is the UTF-8 encoding of a two-character
  // Chinese greeting (3 bytes per character).
  assert(my_strlen("\xe4\xbd\xa0\xe5\xa5\xbd") == 6);
  printf("Passed %s\n", __func__);
}

void TestCase10() {
  // Test Case 10: NULL input is invalid
  assert(my_strlen(NULL) == -1);
  printf("Passed %s\n", __func__);
}

void TestCase11() {
  // Test Case 11: A long string built at runtime
  int n = 1000000;
  char* s = malloc(n + 1);
  assert(s != NULL);
  int i; 
  for ( i = 0; i < n; i++) {
    s[i] = 'a' + i % 26;
  }
  s[n] = '\0';
  assert(my_strlen(s) == n);
  free(s);
  printf("Passed %s (length %d)\n", __func__, n);
}

void TestCase12() {
  // Test Case 12: Agree with the standard strlen on a variety of strings,
  // and do not modify the input
  const char* samples[] = {
    "", "x", "Fudan", "The quick brown fox jumps over the lazy dog",
    "line1\nline2\n", "tab\there", "1234567890", "~!@#$%^&*()_+"
  };
  int count = sizeof(samples) / sizeof(samples[0]);
  int i;
  for ( i = 0; i < count; i++) {
    char copy[64];
    strcpy(copy, samples[i]);
    assert(my_strlen(copy) == (int)strlen(samples[i]));
    assert(strcmp(copy, samples[i]) == 0);
  }
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
  TestCase11();
  TestCase12();
  printf("\nAll tests passed!\n");
  return 0;
}
