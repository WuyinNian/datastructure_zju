#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct HNode *Heap;
struct HNode
{
    ElementType *data; //储存元素的数组
    int size;          //堆中当前元素的个数
    int capacity;      //堆的容量
};
typedef Heap MaxHeap;
#define MAXDATA 1000; //该值应根据具体情况定义为大于堆中所有可能元素的值

MaxHeap creatHeap(int maxSize)
{
    MaxHeap maxH = (MaxHeap)malloc(sizeof(struct HNode));
    maxH->data = (ElementType*)malloc(sizeof(ElementType) * (maxSize + 1));
    maxH->data[0] = MAXDATA; //定义哨兵为大于堆中所有可能的最大值
    maxH->size = 0;
    maxH->capacity = maxSize;
    return maxH;
}
int isFull(MaxHeap maxH)
{
    return maxH->capacity == maxH->size;
}
bool insert(MaxHeap maxH, ElementType x)
{
    if (isFull(maxH))
    {
        printf("heap full\n");
        return false;
    }
    int i = ++maxH->size; // i指向堆的最后一个位置
    //将堆的最大值下沉
    // data[0]为哨兵元素，控制循环结束
    for (; maxH->data[i / 2] < x; i /= 2)
    {
        maxH->data[i] = maxH->data[i / 2];
    }
    maxH->data[i] = x; //插入
    return true;
}
int isEmpty(MaxHeap maxH)
{
    return maxH->size == 0;
}
#define ERROR -1;
ElementType deleteMax(MaxHeap maxH)
{
    if (isEmpty(maxH))
    {
        printf("heap empty\n");
        return ERROR;
    }
    int parent, child;
    ElementType maxItem, temp;
    maxItem = maxH->data[1];         //取出最大值
    temp = maxH->data[maxH->size--]; //保存堆的最后一个元素，准备找到合适的位置存放
    for (parent = 1; 2 * parent <= maxH->size; parent = child)
    {
        child = 2 * parent;                                                   //指向左儿子
        if (child != maxH->size && maxH->data[child] < maxH->data[child + 1]) //判断左儿子是否是最后一个元素 并且找出最大的儿子
            child++;
        if (temp >= maxH->data[child]) //要放置的元素如果大于最大的儿子，说明该parent是该元素要放置的位置
            break;
        else //要放置的元素小于最大的儿子，parent位置元素替换为child位置元素，parent指向child
            maxH->data[parent] = maxH->data[child];
    }
    maxH->data[parent] = temp;
    return maxItem;
}
void filterDown(MaxHeap maxH, int p)
{
    if (isEmpty(maxH))
    {
        printf("heap empty!\n");
        return;
    }
    int parent, child;
    ElementType temp = maxH->data[p];
    for (parent = p; parent * 2 <= maxH->size; parent = child)
    {
        child = parent * 2;
        if (child != maxH->size && maxH->data[child] < maxH->data[child + 1])
        {
            child++;
        }
        if (temp >= maxH->data[child])
            break;
        else
            maxH->data[parent] = maxH->data[child];
    }
    maxH->data[parent] = temp;
}
void buildMaxHeap(MaxHeap maxH)
{
    for (int i = maxH->size / 2; i > 0; i--)
        filterDown(maxH, i);
}