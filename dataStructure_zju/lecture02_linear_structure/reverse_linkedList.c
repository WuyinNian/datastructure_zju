#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000005

int main()
{
    //输入第一行信息
    int firstAdress, K, N = 0;
    scanf("%d %d %d", &firstAdress, &N, &K);

    //用Adress作为下标，将每一行的Data和Next分别存入Data数组和Next数组
    int Adress, *Data, *Next;
    Data = (int *)malloc(MAXSIZE);
    Next = (int *)malloc(MAXSIZE);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &Adress);
        scanf("%d %d", &Data[Adress], &Next[Adress]);
    }

    //将每个结点的Adress按Adress-Next顺序存储在addressList数组中
    int *addList, count = 0; // count用于记录有效结点数
    addList = (int *)malloc(MAXSIZE);
    while (firstAdress != -1)
    {
        addList[count++] = firstAdress;
        firstAdress = Next[firstAdress];
    }

    //将有效结点的地址储存在Result数组中，避免遗漏不翻转的数组
    int *Result;
    Result = (int *)malloc(MAXSIZE);
    for (int i = 0; i < count; i++)
    {
        Result[i] = addList[i];
    }

    /**
     * @brief 柳婼版翻转：根据下标直接找到目标
     * 
        翻转每K个元素组成的子序列，尾巴不翻转
        翻转边界count - count % k
        i / K : 第n个子序列，n从0开始
        i / K * K :第n个子序列的第一个元素下标
        i / K * K + K - 1:第n个子序列的第K个元素下标（即最后一个元素）
        i % K : 子序列第j个元素的下标
        第n个子序列的第K个元素下标（即最后一个元素） -  子序列第j个元素的下标 = 子序列倒数第j个元素的下标
     */
    // for (int i = 0; i < (count - count % K); i++)
    //     Result[i] = addList[i / K * K + K - 1 - i % K];

    /**
     * @brief 双指针法翻转数组
     *
     */
    int temp, left, right;
    for (int i = 0, j = K - 1; j < (count - count % K); i += K, j += K)
    {
        left = i;
        right = j;
        while (left < right)
        {
            temp = Result[left];
            Result[left++] = Result[right];
            Result[right--] = temp;
        }
    }

    free(addList);
    free(Next);

    //打印翻转后的链表
    for (int i = 0; i < count - 1; i++)
        printf("%05d %d %05d\n", Result[i], Data[Result[i]], Result[i + 1]);
    printf("%05d %d -1\n", Result[count - 1], Data[Result[count - 1]]);
    return 0;
}