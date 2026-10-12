#include <stdio.h>
#include <assert.h>

// Converts a given date (year, month, day) to the number of days that have
// elapsed since January 1, Year 1.
//convert把……转换
//that have elapsed	已经过去的 since January 1, Year 1	从公元 1 年 1 月 1 日起
// Convention: date_to_days(1, 1, 1) == 0, date_to_days(1, 1, 2) == 1.
/*Convention	约定 / 规定 / 惯例
date_to_days	（函数名）日期 → 天数
(1, 1, 1)	参数：年=1，月=1，日=1
== 0	结果等于 0
(1, 1, 2)	年=1，月=1，日=2
== 1	结果等于 1
它在规定什么
它在明确告诉你两件事：

第一件：起点是哪天date_to_days(1, 1, 1) == 0
公元 1 年 1 月 1 日 → 返回 0（它是第 0 天）也就是说，起点那天算 0，不是 1。
第二件：怎么数date_to_days(1, 1, 2) == 1
公元 1 年 1 月 2 日 → 返回 1（过了 1 天）也就是从起点往后数，每过一天加 1。
为什么起点要算 0，而不是 1
因为题目说的是：

"the number of days that have elapsed since January 1, Year 1"
（已经过去的天数）

在 1 月 1 日当天，"已经过去的天数"当然是 0——因为一天还没过呢。到 1 月 2 日，才"过去"了 1 天。

这跟年龄是一样的道理：

刚出生那天，你 0 岁

*/
// Leap year rule: a year is a leap year if it is divisible by 4,
// except years divisible by 100, unless also divisible by 400.
//Leap year rule	闰年规则
//a year is a leap year	一个年份是闰年
//if it is divisible by 4	如果它能被 4 整除
//except years divisible by 100	除了能被 100 整除的年份
//unless also divisible by 400	除非它也能被 400 整除
// Returns -1 if the date is invalid (year < 1, month not in 1..12,
// or day not in 1..days_in_month).
int date_to_days(int year, int month, int day) {
  // TODO: implement this function
  // 辅助函数：判断是否为闰年

    // 1. 校验输入合法性
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return -1;
    }
    
    int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

    
    // 每个月的天数（下标1对应1月，下标2用于暂存平年的28天）
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // 如果是闰年，2月改为29天
    if (is_leap_year(year)) {
        days_in_month[2] = 29;
    }
    
    // 检查日期是否超出当月最大天数
    if (day > days_in_month[month]) {
        return -1;
    }
    
    // 2. 计算天数
    long long total_days = 0;
    
    // (1) 计算之前所有完整年份的天数
    int prev_years = year - 1;
    total_days += prev_years * 365LL; // 平年总天数
    // 加上之前的闰年个数：逢4一闰，逢100不闰，逢400再闰
    total_days += prev_years / 4;
    total_days -= prev_years / 100;
    total_days += prev_years / 400;
    
    // (2) 加上当前年份中，本月之前所有月份的天数
    int i;
    for ( i = 1; i < month; i++) {
        total_days += days_in_month[i];
    }
    
    // (3) 加上当月的天数
    total_days += day;
    
    // 3. 返回结果
    // 题目约定：date_to_days(1, 1, 1) == 0
    // 因为上面算出来 1 月 1 日是 1 天，所以要减去 1 来调整基准
    return (int)(total_days - 1);
}
  


void TestCase1() {
  // Test Case 1: 2016-02-29 (leap year, valid)
  int days = date_to_days(2016, 2, 29);
  assert(days == 736022);
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  // Test Case 2: 2017-02-29 (common year, invalid)
  int days = date_to_days(2017, 2, 29);
  assert(days == -1);
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // Test Case 3: 2024-10-12
  int days = date_to_days(2024, 10, 12);
  assert(days == 739170);
  printf("Passed %s\n", __func__);
}

void TestCase4() {
  // Test Case 4: Century non-leap year 1900-02-29 (should be invalid)
  int days = date_to_days(1900, 2, 29);
  assert(days == -1);
  printf("Passed %s\n", __func__);
}

void TestCase5() {
  // Test Case 5: Day 31 in months with only 30 days (should be invalid)
  int months_with_30_days[] = {4, 6, 9, 11};
  int year = 2024;
  
  int i;
  for (i = 0; i < 4; i++) {
    int month = months_with_30_days[i];
    int result = date_to_days(year, month, 31);
    assert(result == -1);
  }
  printf("Passed %s\n", __func__);
}

void TestCase6() {
  // Test Case 6: Century leap year 2000-02-29 (divisible by 400, valid)
  int days = date_to_days(2000, 2, 29);
  assert(days == 730178);
  printf("Passed %s\n", __func__);
}

void TestCase7() {
  // Test Case 7: Boundary values at the very beginning of the calendar
  assert(date_to_days(1, 1, 1) == 0);
  assert(date_to_days(1, 1, 2) == 1);
  assert(date_to_days(1, 12, 31) == 364);
  assert(date_to_days(2, 1, 1) == 365);
  printf("Passed %s\n", __func__);
}

void TestCase8() {
  // Test Case 8: Day 31 in months with 31 days (should be valid)
  int months_with_31_days[] = {1, 3, 5, 7, 8, 10, 12};
  int year = 2024;
  
int i;
  for (i = 0; i < 7; i++) {
    int month = months_with_31_days[i];
    int result = date_to_days(year, month, 31);
    assert(result != -1);
  }
  printf("Passed %s\n", __func__);
}

void TestCase9() {
  // Test Case 9: Out-of-range month, day, and year (should be invalid)
  assert(date_to_days(2024, 0, 1) == -1);    // month too small
  assert(date_to_days(2024, 13, 1) == -1);   // month too large
  assert(date_to_days(2024, 1, 0) == -1);    // day too small
  assert(date_to_days(2024, 1, -5) == -1);   // negative day
  assert(date_to_days(2024, 2, 30) == -1);   // Feb 30 in a leap year
  assert(date_to_days(0, 1, 1) == -1);       // year 0 does not exist
  assert(date_to_days(-1, 1, 1) == -1);      // negative year
  printf("Passed %s\n", __func__);
}

void TestCase10() {
  // Test Case 10: Consecutive dates across month and year boundaries
  assert(date_to_days(2023, 12, 31) + 1 == date_to_days(2024, 1, 1));
  assert(date_to_days(2024, 2, 29) + 1 == date_to_days(2024, 3, 1));
  assert(date_to_days(2023, 2, 28) + 1 == date_to_days(2023, 3, 1));
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
