#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXSIZE 100
#define ERROR (ElementType) - 1

typedef int TreeElementType; //树结点储存的类型
typedef struct TNode *Position;
typedef Position BinTree; /* 二叉树类型 */
struct TNode
{                         /* 树结点定义 */
    TreeElementType Data; /* 结点数据 */
    BinTree Left;         /* 指向左子树 */
    BinTree Right;        /* 指向右子树 */
};

typedef BinTree ElementType;
typedef struct SNode *PtrToNode;
typedef PtrToNode Stack;
struct SNode
{
    ElementType Data;
    Stack Next;
};

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

//先序遍历
void PreOrderTraversal(BinTree binT)
{
    BinTree T = binT;
    binT = (BinTree)malloc(sizeof(struct TNode));
    Stack S = creatStack();
    while (T || !isEmpty(S)) //树或堆栈不空，一直循环
    {
        while (T) //一直向左，沿路将结点压入栈中
        {
            push(S, T); // T结点入栈，第一次访问到中结点
            printf("%d\n", T->Data);
            T = T->Left;
        } //循环结束访问到T的最后一个左子结点，此时栈顶为T

        if (!isEmpty(S))
        {
            T = pop(S);   // T结点出栈，访问回T
            T = T->Right; //访问到T结点右子树
        }
    }
}
//中序遍历
void InOrderTraversal(BinTree binT)
{
    BinTree T = binT;
    Stack S = creatStack();
    while (T || !isEmpty(S)) //树或堆栈不空，一直循环
    {
        while (T) //一直向左，沿路将结点压入栈中
        {
            push(S, T); // T结点入栈，第一次访问到中结点
            T = T->Left;
        } //循环结束访问到T的最后一个左子结点，此时栈顶为T

        if (!isEmpty(S))
        {
            T = pop(S); // T结点出栈，访问回T
            printf("%d\n", T->Data);
            T = T->Right; //访问到T结点右子树
        }
    }
}
//后序遍历
void PostOrderTraversal(BinTree binT)
{
    BinTree T = binT;
    Stack S = creatStack(); /*创建并初始化堆栈S*/
    BinTree lastT;
    while (T || !isEmpty(S))
    {
        if (T)
        {
            push(S, T);
            T = T->Left;
        }
        else
        {
            T = pop(S); /*获取T的信息*/
            push(S, T); /*获取T的信息*/
            if (T->Right && T->Right != lastT) // T的右边存在 且没有被访问过
            {
                T = T->Right; //让右边的入栈
                push(S, T);
                T = T->Left; //指向右边的左结点
            }
            else // T的右边不存在或被访问过 就出栈
            {
                T = pop(S);
                printf("%d\n", T->Data); /*(访问)打印结点*/
                lastT = T; //用r记录打印的节点
                T = NULL;
            }
        }
    }

}

typedef BinTree ElementType;
struct QNode
{
    int maxSize;            //最大容量(存放个数为maxSize-1,需要留出一个位置判断队列满)
    ElementType *data;      //储存元素的数组
    int front, rear;   //队列头尾指针
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

bool isEmptyQ(Queue Q)
{
    return Q->rear == Q->front;
}

ElementType deleteQ(Queue Q)
{
    if (isEmptyQ(Q))
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

void levelOrderTraversal(BinTree binT)
{
    BinTree T = binT;
    if (!T)
        return;
    Queue Q = creatQueue(MAXSIZE);
    addQ(Q,T);
    while(!isEmptyQ(Q))
    {
        T = deleteQ(Q);//取出父结点
        printf("%d\n",T->Data);
        if(T->Left) addQ(Q,T->Left);//放入父结点的左结点
        if(T->Right) addQ(Q,T->Right);//放入父结点的右结点
    }
}

int main()
{
    BinTree T1;
    T1 = (BinTree)malloc(sizeof(struct TNode));
    BinTree T2;
    T2 = (BinTree)malloc(sizeof(struct TNode));
    BinTree T3;
    T3 = (BinTree)malloc(sizeof(struct TNode));
    T1->Data = 1;
    T2->Data = 2;
    T3->Data = 3;
    T1->Left = T2;
    T1->Right = T3;
    // PreOrderTraversal(T1);
    // InOrderTraversal(T1);
    // PostOrderTraversal(T1);
    levelOrderTraversal(T1);
    return 0;
}