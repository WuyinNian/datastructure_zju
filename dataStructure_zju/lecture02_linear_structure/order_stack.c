#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10
#define ERROR (ElementType) -1

typedef int ElementType;
typedef int Position;
struct SNode
{
    ElementType *data; //储存元素的数组
    Position top;      //栈顶指针
    int maxSize;       //栈的最大尺寸
};
typedef struct SNode *Stack;

/**
 * @brief 创建栈对象
 *
 * @param maxSize
 * @return Stack
 */
Stack createStack(int maxSize)
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    S->top = -1;
    S->maxSize = maxSize;
    return S;
}

bool isFull(Stack S)
{
    return (S->top == S->maxSize - 1);
}
bool push(Stack S, ElementType X)
{
    if (isFull(S))
    {
        printf("栈满");
        return false;
    }
    else
    {
        S->data[++(S->top)] = X;
        return true;
    }
}

bool isEmpty(Stack S)
{
    return (S->top == -1);
}
ElementType Pop(Stack S)
{
    if (isEmpty(S))
    {
        printf("栈空");
        return ERROR;
    }
    else
        return S->data[(S->top)--];

}
