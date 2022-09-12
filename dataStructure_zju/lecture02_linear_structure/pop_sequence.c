#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct SNode
{
    int *data;
    int top;
    int maxsize;
};
typedef struct SNode *Stack;
Stack creatStack(int maxsize)
{
    Stack s = (Stack)malloc(sizeof(struct SNode));
    s->data = (int *)malloc(maxsize);
    s->maxsize = maxsize;
    s->top = -1;
    return s;
}
bool sIsEmpty(Stack s)
{
    return s->top == -1;
}
bool sIsFull(Stack s)
{
    return s->top == s->maxsize - 1;
}
void sPush(Stack s, int x)
{
    if (sIsFull(s))
    {
        printf("FULL");
        return;
    }
    s->data[++s->top] = x;
}
int sPop(Stack s)
{
    if (sIsEmpty(s))
    {
        printf("EMPTY");
        return -1;
    }
    return s->data[s->top--];
}

int main()
{
    //输入栈的大小M，原始队列的长度N，需要判断的队列数K
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);

    for (int i = 0; i < K; i++)
    {
        Stack s = creatStack(M+1);
        int q[N+1];
        for (int i = 1; i <= N; i++)
        {
            scanf("%d", &q[i]);
        }
        int current = 1;
        for (int i = 1; i <= N; i++)
        {
            sPush(s, i);
            if (s->top+1 > M)
                break;
            while(!sIsEmpty(s) && s->data[s->top] == q[current])
            {
                sPop(s);
                current++;
            }
        }
        if (current == N+1)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
        free(s);
    }
    return 0;
}
