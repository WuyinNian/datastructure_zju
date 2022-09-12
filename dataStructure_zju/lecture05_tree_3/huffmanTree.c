#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    int weight;
    char c;
    HuffmanTree left, right;
};

typedef HuffmanTree ElementType;
typedef struct HNode *Heap;
struct HNode
{
    ElementType *data; //储存元素的数组
    int size;          //堆中当前元素的个数
    int capacity;      //堆的容量
};
typedef Heap MinHeap;
#define MINDATA -1000; //该值应根据具体情况定义为小于堆中所有可能元素的值

MinHeap creatHeap(int maxSize)
{
    MinHeap minH = (MinHeap)malloc(sizeof(struct HNode));
    minH->data = (ElementType *)malloc(sizeof(struct TreeNode *) * maxSize + 1);
    minH->data[0] = (ElementType)malloc(sizeof(struct TreeNode));
    minH->data[0]->weight = MINDATA; //定义哨兵为小于堆中所有可能的最小值
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
    int i = ++minH->size; // i指向插入堆后的最后一个位置
    //将堆的最小值下沉
    // data[0]为哨兵元素，控制循环结束
    for (; minH->data[i / 2]->weight > x->weight; i /= 2)
    {
        minH->data[i] = minH->data[i / 2];
    }
    minH->data[i] = x; //插入
    return true;
}
int isEmpty(MinHeap minH)
{
    return minH->size == 0;
}

ElementType deleteMin(MinHeap minH)
{
    if (isEmpty(minH))
    {
        printf("heap empty\n");
        return NULL;
    }
    int parent, child;
    ElementType minItem, temp;
    minItem = minH->data[1];         //取出最小值
    temp = minH->data[minH->size--]; //保存堆的最后一个元素，准备找到合适的位置存放
    for (parent = 1; 2 * parent <= minH->size; parent = child)
    {
        child = 2 * parent;                                                                   //指向左儿子
        if (child != minH->size && minH->data[child]->weight > minH->data[child + 1]->weight) //判断左儿子是否是最后一个元素 并且找出最小的儿子
            child++;
        if (temp->weight <= minH->data[child]->weight) //要放置的元素如果小于最小的儿子，说明该parent是该元素要放置的位置
            break;
        else //要放置的元素大于于最小的儿子，parent位置元素替换为child位置元素，parent指向child
            minH->data[parent] = minH->data[child];
    }
    minH->data[parent] = temp;
    return minItem;
}
void filterDown(MinHeap minH, int p)
{
    if (isEmpty(minH))
    {
        printf("heap empty!\n");
        return;
    }
    int parent, child;
    ElementType temp = minH->data[p];
    for (parent = p; parent * 2 <= minH->size; parent = child)
    {
        child = parent * 2;
        if (child != minH->size && minH->data[child]->weight > minH->data[child + 1]->weight) //找出最大频率（权重）最大的子结点
        {
            child++;
        }
        if (temp->weight <= minH->data[child]->weight) //必须等号，否则相等情况下，二者位置会调换
            break;
        else
            minH->data[parent] = minH->data[child];
    }
    minH->data[parent] = temp;
}
void buildMinHeap(MinHeap minH)
{
    for (int i = minH->size / 2; i > 0; i--)
        filterDown(minH, i);
}

HuffmanTree creatHuffmanTree(MinHeap minH)
{
    //假设权值已经储存在minH->data[i]->weight中
    HuffmanTree huffmanT;
    buildMinHeap(minH);
    for (int i = 1; i < minH->capacity; i++) //这边必须用capacity，因为size会随delete改变
    {
        huffmanT = (HuffmanTree)malloc(sizeof(struct TreeNode));
        huffmanT->left = deleteMin(minH);
        huffmanT->right = deleteMin(minH);
        huffmanT->weight = huffmanT->left->weight + huffmanT->right->weight;
        insert(minH, huffmanT);
    }
    huffmanT = deleteMin(minH);
    return huffmanT;
}
