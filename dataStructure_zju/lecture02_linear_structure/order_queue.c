#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR (ElementType) - 1

typedef int ElementType;
typedef int Position;
struct QNode
{
    int maxSize;            //最大容量(存放个数为maxSize-1,需要留出一个位置判断队列满)
    ElementType *data;      //储存元素的数组
    Position front, rear;   //队列头尾指针
};
typedef struct QNode *Queue;

Queue creatQueue(int maxSize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    Q->maxSize = maxSize;
    Q->front = 0;
    Q->rear = 0;
    return Q;
}

bool isFull(Queue Q)
{
    return (Q->rear+1) % Q->maxSize == Q->front;
}
bool addQ(Queue Q, ElementType X)
{
    if (isFull(Q))
    {
        printf("Queue Full!\n");
        return false;
    }
    else
    {
        Q->rear = (Q->rear + 1) % Q->maxSize;
        Q->data[Q->rear] = X;
        return true;
    }
}

bool isEmpty(Queue Q)
{
    return Q->rear == Q->front;
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
        Q->front = (Q->front + 1) % Q->maxSize;
        return Q->data[Q->front];
    }
}
