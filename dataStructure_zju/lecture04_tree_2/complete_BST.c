#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 1005

int result[N]; //记录结果
int value[N];  //储存输入的数

void complete_BST(int left, int right, int root);
int getLeftNodes(int n);

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    int n;
    scanf("%d", &n);
    int num;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        value[i] = num;
    }
    qsort(value, n, sizeof(int), compare);

    complete_BST(0, n - 1, 0);
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", result[i]);
    }
    printf("%d\n", result[n - 1]);
    return 0;
}

void complete_BST(int left, int right, int root)
{
    int length = right - left + 1;
    if (length == 0)
        return;

    int leftNodes = getLeftNodes(length);
    result[root] = value[left + leftNodes];

    int leftRoot = root * 2 + 1;
    int rightRoot = leftRoot + 1;
    complete_BST(left, left + leftNodes - 1, leftRoot);
    complete_BST(left + leftNodes + 1, right, rightRoot);
}
int getLeftNodes(int n)
{
    int height = log2(n + 1);               //完美二叉树的高度
    int lastLayer = n - pow(2, height) + 1; //最下面一层的结点个数
    //如果最后一层的结点个数超过左子树的范围，就取最后一层最大结点数的一半
    lastLayer = lastLayer < pow(2, height - 1) ? lastLayer : pow(2, height - 1);
    int result = pow(2, height - 1) - 1 + lastLayer; // 最下面一层的个数 加上 其上的左子完美二叉树
    return result;
}