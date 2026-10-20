#include <stdio.h>
#include <assert.h>
#include <math.h>

// Given a string数组, compute计算 the relative frequency相对频率 of each letter 'a' to 'z'.
//
// - Only letters are counted; all non-letter characters are ignored.
// - Uppercase and lowercase letters大写和小写字母 are treated as the same.
// - freq[i] = (number of occurrences of the i-th letter)
//             / (total number of letters in str)
//   so the 26 values add up to 1 whenever str contains at least one letter.
// - If str contains no letters at all (e.g. the empty string),
//   all 26 entries of freq must be set to 0.
//
// freq[0] corresponds to 'a'
// freq[1] corresponds to 'b'
// ...
// freq[25] corresponds to 'z'
void frequency(const char *str, double *freq) {
    int count[26]={0};//大括号是初始化数组的意思，所有数字全是0 
    int total=0;
    
    int i;
    for(i=0;str[i]!='\0';i++)//遍历数组的意思
	//只要不是结束符'\0'就继续 
    {
        if (isalpha((unsigned char)str[i])) 
        //判断当前位是否是字母
		//isalpha 是 <ctype.h> 里的函数，是字母返回非 0（真），否则返回 0（假）
		// "把 str[i] 这个字符转成无符号字符，然后交给 isalpha 判断它是不是字母。"
		{
            int idx = tolower((unsigned char)str[i]) - 'a';
            //tolower(...)：大写转小写，小写不变
            //- 'a'：利用 ASCII 码的连续性求偏移。
     //'a' 的 ASCII 是 97。
//'a' - 'a' = 0，'b' - 'a' = 1，'z' - 'a' = 25。

//C 里用单引号包起来的单个字符，叫字符常量
//这些字符常量在 C 里本质都是整数，具体值是它的 ASCII 码


//结果 idx 正好是 0~25 之间的下标。

//'C' → tolower → 'c' → 'c' - 'a' = 2，所以 idx = 2，对应 count[2]（第 3 个字母 c）
            count[idx]++;
            total++;
        }
    }

    // 计算频率
    if (total == 0) {
        // 没有字母，全部置 0
        int i;
        for ( i = 0; i < 26; i++) {
            freq[i] = 0.0;
        }
    } else {
        for (i = 0; i < 26; i++) {
            freq[i] = (double)count[i] / total;
        }
    }
}
    
    	

static int double_equals(double a, double b) {
  const double EPSILON = 1e-9;
  return fabs(a - b) < EPSILON;
}

void TestCase1() {
  // test with "Hello, World!"
  const char *str = "Hello, World!";
  double freq[26] = {0};  // freq[26] is used to store the results
  double expected_freq[26] = {0}; // expected_freq[26] is used to store expected results
  expected_freq['h' - 'a'] = 1.0 / 10;
  expected_freq['e' - 'a'] = 1.0 / 10;
  expected_freq['l' - 'a'] = 3.0 / 10;
  expected_freq['o' - 'a'] = 2.0 / 10;
  expected_freq['r' - 'a'] = 1.0 / 10;
  expected_freq['w' - 'a'] = 1.0 / 10;
  expected_freq['d' - 'a'] = 1.0 / 10;
  frequency(str, freq);
  int i;
  for( i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  //test with "AaBbCc"
  const char *str = "AaBbCc";
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  expected_freq['a' - 'a'] = 2.0 / 6;
  expected_freq['b' - 'a'] = 2.0 / 6;
  expected_freq['c' - 'a'] = 2.0 / 6;
  frequency(str, freq);
  int i;
  for( i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // test with empty string
  const char *str = ""; // empty string
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  frequency(str, freq);
  int i;
  for( i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase4() {
  // test with all letters
  const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  int i;
  for (i = 0; i < 26; i++) {
    expected_freq[i] = 2.0 / 52; // each letter appears twice
  }
  frequency(str, freq);
  for( i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase5() {
  // test with mixed case and repeated letters
  const char *str = "MMmmNnnOOOopPPpQRRrrrrr";
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  expected_freq['m' - 'a'] = 4.0 / 23;
  expected_freq['n' - 'a'] = 3.0 / 23;
  expected_freq['o' - 'a'] = 4.0 / 23;
  expected_freq['p' - 'a'] = 4.0 / 23;
  expected_freq['q' - 'a'] = 1.0 / 23;
  expected_freq['r' - 'a'] = 7.0 / 23;
  frequency(str, freq);
  int i;
  for( i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  TestCase4();
  TestCase5();
  printf("\nAll tests passed!\n");
  return 0;
}
