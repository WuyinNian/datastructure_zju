#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ERROR (ElementType) - 1

typedef int ElementType;
struct SNode
{
    ElementType Data;
    Stack Next;
};
typedef struct SNode *PtrToNode;
typedef PtrToNode Stack;

/**
 * @brief 构建一个堆栈的头结点，返回该结点指针
 *
 * @return Stack
 */
Stack creatStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

bool push(Stack S, ElementType X)
{
    //构建要压入的结点
    PtrToNode newNode;
    newNode = (PtrToNode)malloc(sizeof(struct SNode));
    newNode->Data = X;

    //入栈
    newNode->Next = S->Next;
    S->Next = newNode;
    return true;
}

bool isEmpty(Stack S)
{
    return (S->Next == NULL);
}
ElementType pop(Stack S)
{
    PtrToNode delNode;
    ElementType topElem;
    if (isEmpty(S))
    {
        printf("栈空！");
        return ERROR;
    }
    else
    {
        delNode = S->Next;
        topElem = delNode->Data;
        S->Next = delNode->Next;
        free(delNode);
        return topElem;
    }
}
