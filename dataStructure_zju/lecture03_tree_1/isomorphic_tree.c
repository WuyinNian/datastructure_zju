#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXSIZE 100
#define Null -1
typedef char ElementType;
typedef struct TNode Tree;
struct TNode
{
    ElementType element;
    int left, right;
} T1[MAXSIZE], T2[MAXSIZE];

//构建树
int buildTree(Tree T[])
{
    int N;
    scanf("%d\n", &N);
    int check[N]; //用来标记元素的左右结点是否存在，无其他结点指向的结点即根结点
    int root;
    if (N)
    {
        for (int i = 0; i < N; i++)
            check[i] = 0;//重置flag
        for (int i = 0; i < N; i++)
        {
            scanf("%c %c %c\n", &T[i].element, &T[i].left, &T[i].right);
            //
            T[i].left = (T[i].left == '-') ? Null : T[i].left - '0';
            check[T[i].left] = (T[i].left == '-') ? 0 : 1;
            T[i].right = (T[i].right == '-') ? Null : T[i].right - '0';
            check[T[i].right] = (T[i].right == '-') ? 0 : 1;
        }
        for (int i = 0; i < N; i++)
        {
            if (!check[i]) // check[i] == 0,找到根结点
            {
                root = i;
                break;
            }
        }
    }
    else
    {
        root = Null; // N=0,空树
    }
    return root;
}

bool isomorphic(int R1, int R2)
{
    //两棵树都空
    if (R1 == Null && R2 == Null)
        return true;
    //只有一棵树空
    if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null))
        return false;
    //都不空，根的值不同
    if (T1[R1].element != T2[R2].element)
        return false;
    //都不空，根的值相同，都没有左子树
    if (T1[R1].left == Null && T2[R2].left == Null)
        return isomorphic(T1[R1].right, T2[R2].right); //比较右子树
    //都不空，根的值相同，都有左子树，且左子树的值相同
    if ((T1[R1].left != Null && T2[R2].left != Null) &&
        (T1[T1[R1].left].element == T2[T2[R2].left].element))
        return isomorphic(T1[R1].right, T2[R2].right) &&
               isomorphic(T1[R1].left, T2[R2].left); //比较左子树和右子树
    else                                             //都不空，根的值相同，一个有左子树，一个没有左子树
        return isomorphic(T1[R1].left, T2[R2].right) &&
               isomorphic(T1[R1].right, T2[R2].left);
}

int main()
{
    int R1, R2;
    R1 = buildTree(T1);
    R2 = buildTree(T2);
    if (isomorphic(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
