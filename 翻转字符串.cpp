#include <string.h> 

void string_reverse(char* str) {
	/*char* str = 指向字符的指针，用来接收一个字符串（的首地址），通过它可以读取和修改整串字符。*/
	 // 定义一个函数 string_reverse，参数为字符指针 str，无返回值
    int left = 0;           
	//    定义左索引 left，初始化为 0（指向字符串开头）
    int right = strlen(str) - 1; 
   // 定义右索引 right，初始化为字符串长度减 1（指向字符串末尾） 
   //strlen(str)算出字符串的长度（从 str 指向的位置开始，数到 '\0' 之前有多少个字符）。
    while (left < right) {
       
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
         // 把左边字符暂存到 temp
            // 把右边字符赋给左边位置
                // 把暂存的左边字符赋给右边位置（完成交换）
        //str[left] 是 C 语言里的数组下标访问写法，用在指针上时表示：
		//取 str 指向的那个字符串里、下标为 left 的那个字符。
        left++;
        right--;
         // 左索引右移一位
                         // 右索引左移一位
    }
}

