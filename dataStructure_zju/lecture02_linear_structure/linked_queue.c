#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR (ElementType) - 1

typedef int ElementType;
struct Node
{
    ElementType data;
    PtrToNode next;
};
typedef struct Node *PtrToNode;
typedef PtrToNode Position;

struct QNode
{
    Position rear, front;
};
typedef struct QNode *Queue;

Queue creatQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    return Q;
}

bool addQ(Queue Q, ElementType X)
{
    //创建要加入队列的结点
    PtrToNode newNode;
    newNode = (PtrToNode)malloc(sizeof(struct Node));
    newNode->data = X;

    if (Q->front->next == NULL)//如果队头没有元素，对头先指向第一个元素
    {
        Q->front->next = newNode;
    }
    Q->rear->next = newNode;
    Q->rear = Q->rear->next;//队尾指针后移
    return true;
}

bool isEmpty(Queue Q)
{
    return Q->front == NULL;
}
ElementType deleteQ(Queue Q)
{
    if (isEmpty(Q))
    {
        printf("Queue Empty!");
        return ERROR;
    }
    else
    {
        PtrToNode delNode = Q->front;
        if (Q->front == Q->rear)//如果队列只有一个元素
            Q->front == Q->rear == NULL;//删除后队列位置为空
        else
            Q->front = Q->front->next;
        free(delNode);
        return delNode->data;
    }
}
