int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i;
    int j;
    for(i=0;i<numsSize;i++)
    {
        for(j=i+1;j<numsSize;j++)
        {
            if(nums[i]+nums[j]==target)
            {
        int* result = (int*)malloc(2 * sizeof(int));
        //向系统借一块能放 2 个 int 的内存，用指针 result 指向它。
//sizeof(int)：一个 int 占几个字节（通常是 4）
//2 * sizeof(int)：2 个 int 需要几个字节（通常 8）
//malloc(8)：向堆申请 8 字节，返回这块内存的首地址（类型是 void*）
//(int*)：把 void* 转成 int*，表示「我按 int 数组来用」
//int* result = ...：用 result 记住这块内存的地址
                if (result == NULL) {
                    *returnSize = 0;
                    return NULL;
                }
                result[0] = i;
                result[1] = j;
                //把两个下标填进刚借的内存。
//result 是 int*，所以 result[0] 是第一个 int，result[1] 是第二个 int。
                *returnSize = 2;
                return result;
        }
    }
     }
     *returnSize = 0;
    return NULL;
}
