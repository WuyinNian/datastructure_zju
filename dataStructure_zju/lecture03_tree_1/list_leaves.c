#include <stdio.h>
#include <stdlib.h>
#define Null -1
#define MaxTree 10
#define Tree int

struct TreeNode
{
    int Data;
    Tree Left;
    Tree Right;
} T[MaxTree], quene[MaxTree];

int first = -1, last = -1;

Tree BuildTree(struct TreeNode T[]);
void Push(struct TreeNode TN);
struct TreeNode Pop();
void PrintLeaves(Tree R);

int N, check[MaxTree];

int main()
{
    Tree R;
    R = BuildTree(T);
    PrintLeaves(R);
    return 0;
}

Tree BuildTree(struct TreeNode T[])
{
    int i, Root;
    char cl, cr;
    scanf("%d", &N);
    if (N)
    {
        for (i = 0; i < N; i++)
            check[i] = 0;
        for (i = 0; i < N; i++)
        {
            T[i].Data = i;
            scanf("\n%c %c", &cl, &cr);
            if (cl != '-')
            {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else
                T[i].Left = Null;
            if (cr != '-')
            {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else
                T[i].Right = Null;
        }
        for (i = 0; i < N; i++)
            if (!check[i])
                break;
        Root = i;
    }
    return Root;
}

void Push(struct TreeNode TN)
{
    quene[++last] = TN;
}

struct TreeNode Pop()
{
    return quene[++first];
}

void PrintLeaves(Tree R)
{
    int leaves[N];
    int i, k = 0;
    struct TreeNode tmp;
    Push(T[R]);
    for (i = 0; i < N; i++)
    {
        tmp = Pop();
        if (tmp.Left == -1 && tmp.Right == -1)
            leaves[k++] = tmp.Data;
        if (tmp.Left != -1)
            Push(T[tmp.Left]);
        if (tmp.Right != -1)
            Push(T[tmp.Right]);
    }
    for (i = 0; i < k - 1; i++)
        printf("%d ", leaves[i]);
    printf("%d\n", leaves[k - 1]);
}
