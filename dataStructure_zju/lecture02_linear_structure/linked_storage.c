#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//线性表的链式存储

typedef int ElementType;
typedef struct LNode *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;
struct LNode
{
    ElementType Data;
    List Next;
};

/**
 * @brief 查找
 *
 * @param X
 * @param PtrL
 * @return Position
 */
Position Find(List L, ElementType X)
{
    Position P = L;
    while (P && P->Data != X)
    {
        P = P->Next;
    }
    return P;
}

/**
 * @brief 插入
 *
 * @param PtrL
 * @param P 在P之前插入新结点
 * @param X
 * @return true
 * @return false
 */
bool Insert(List L, Position P, ElementType X)
{
    Position temp, pre;

    //查找P的前一结点
    for (pre = L; pre && pre->Next != P; pre = pre->Next)
        ;

    if (pre == NULL)
    {
        printf("EORROR parameter\n");
        return false;
    }
    else //找到前一个结点
    {
        //申请空间创建待插入结点
        temp = (Position)malloc(sizeof(struct LNode));
        temp->Data = X;

        temp->Next = P;
        pre->Next = temp;

        return true;
    }
}

bool Delete(List L, Position P)
{
    List pre, temp;

    //查找P的前一结点
    for (pre = L; pre && pre->Next != P; pre = pre->Next)
        ;

    if (pre == NULL || P == NULL)
    {
        printf("EORROR parameter\n");
        return false;
    }
    else
    {
        pre->Next = P->Next;
        free(P);
    }

    return true;
}

int main()
{

    return 0;
}