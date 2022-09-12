#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct HNode *Heap;
struct HNode
{
    ElementType *data; //储存元素的数组
    int size;          //堆中当前元素的个数
    int capacity;      //堆的容量
};
typedef Heap MinHeap;
#define MINDATA -10001; //该值应根据具体情况定义为小于堆中所有可能元素的值

MinHeap creatHeap(int maxSize)
{
    MinHeap minH = (MinHeap)malloc(sizeof(struct HNode));
    minH->data = (ElementType *)malloc(sizeof(ElementType) * (maxSize + 1));
    minH->data[0] = MINDATA; //定义哨兵为小于堆中所有可能的最小值
    minH->size = 0;
    minH->capacity = maxSize;
    return minH;
}
int isFull(MinHeap minH)
{
    return minH->capacity == minH->size;
}
bool insert(MinHeap minH, ElementType x)
{
    if (isFull(minH))
    {
        printf("heap full\n");
        return false;
    }
    int i = ++minH->size; // i指向堆的最后一个位置
    //将堆的最小值下沉
    // data[0]为哨兵元素，控制循环结束
    for (; minH->data[i / 2] > x; i /= 2)
    {
        minH->data[i] = minH->data[i / 2];
    }
    minH->data[i] = x; //插入
    return true;
}
void printfPath(MinHeap minH, int index)
{
    if (index > minH->size)
    {
        printf("index illegal!\n");
        return;
    }
    for (; index > 1; index /= 2)
    {
        printf("%d ", minH->data[index]);
    }
    if (index == 1)
        printf("%d\n", minH->data[index]);
}

int main()
{
    int n, k, x;
    scanf("%d %d", &n, &k);
    MinHeap minH = creatHeap(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        insert(minH, x);
    }
    int index;
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &index);
        printfPath(minH, index);
    }

    return 0;
}