#include <stdio.h>
#include <stdbool.h>

//线性表的顺序存储
#define MAXSIZE 1000

typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last;
};

//初始化
List MakeEmpty()
{
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL->Last = -1;
    return PtrL;
}

//查找
#define ERROR -1
Position Find(List PtrL, ElementType Target)
{
    Position i = 0;
    //找到 或者 找到至最后一个元素，退出循环 
    while (PtrL->Data[i] != Target && i < PtrL->Last + 1)
        i++;

    if (i == PtrL->Last + 1)
        return ERROR;
    else
        return i;
}

//插入
/**
 * @brief 
 * 
 * @param PtrL 
 * @param P 要插入的下标位置
 * @param X 
 * @return true 
 * @return false 
 */
bool Insert(List PtrL, Position P, ElementType X)
{
    if (PtrL->Last == MAXSIZE - 1)
    {
        printf("表满！");
        return false;
    }

    if (P < 0 || P > PtrL->Last + 1)
    {
        printf("位置不合法");
        return false;
    }
    for (int i = PtrL->Last; i >= P; i--)
    {
        PtrL->Data[i + 1] = PtrL->Data[i];//将P位置及以后的位置 由后向前 依次后移
    }
    PtrL->Data[P] = X;
    PtrL->Last++;
    return true;
}

bool Delete(List PtrL, Position P)
{
    if (P < 0 || P > PtrL->Last)
    {
        printf("找不到该元素");
        return false;
    }
    for (int i = P+1; i <= PtrL->Last; i++)
    {
        PtrL->Data[i - 1] = PtrL->Data[i];//将P+1位置及以后的元素 由前往后 向前移动
    }
    PtrL->Last--;
    return true;
}

int main()
{

    return 0;
}