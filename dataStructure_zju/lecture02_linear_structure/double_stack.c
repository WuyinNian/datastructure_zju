#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 10
#define ERROR (ElementType) - 1

typedef int ElementType;
typedef struct DNode *Stack;
struct DNode
{
    ElementType Data[MAXSIZE];
    int Top1;
    int Top2;
};
void CreatDstack(Stack PtrS)
{
    PtrS->Top1 = -1;
    PtrS->Top2 = MAXSIZE;
}

bool IsFull(Stack PtrS)
{
    return PtrS->Top1 - PtrS->Top2 == 1;
}
void Push(Stack PtrS, ElementType item, int Tag)
{
    if (IsFull(PtrS))
    {
        printf("栈满");
        return;
    }
    if (Tag == 1)
        PtrS->Data[++(PtrS->Top1)] = item;
    else
        PtrS->Data[--(PtrS->Top2)] = item;
}

bool IsEmpty(Stack PtrS, int Tag)
{
    if (Tag == 1)
        return PtrS->Top1 == -1;
    else
        return PtrS->Top2 == MAXSIZE;
}
ElementType Pop(Stack PtrS, int Tag)
{
    if (IsEmpty(PtrS, Tag))
    {
        printf("栈%d空", Tag);
        return ERROR;
    }
    if (Tag == 1)
        return PtrS->Data[(PtrS->Top1)--];
    else
        return PtrS->Data[(PtrS->Top2)++];
}
