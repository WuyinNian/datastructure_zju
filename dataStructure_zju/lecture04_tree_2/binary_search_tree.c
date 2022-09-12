#include <stdio.h>
#include <stdlib.h>
typedef int ElementType; //树结点储存的类型
typedef struct TNode *Position;
typedef Position BinTree; /* 二叉树类型 */
struct TNode
{                     /* 树结点定义 */
    ElementType Data; /* 结点数据 */
    BinTree Left;     /* 指向左子树 */
    BinTree Right;    /* 指向右子树 */
};
Position find(BinTree bst, ElementType x)
{
    if (!bst)
        return NULL;
    if (bst->Data < x)
    {
        return find(bst->Right, x);
    }
    else if (bst->Data > x)
    {
        return find(bst->Left, x);
    }
    else
    {
        return bst;
    }
}
Position iterFind(BinTree bst, ElementType x)
{
    while (bst)
    {
        if (bst->Data < x)
        {
            bst = bst->Right;
        }
        else if (bst->Data > x)
        {
            bst = bst->Left;
        }
        else
        {
            return bst;
        }
    }
    return NULL;
}
Position findMin(BinTree bst)
{
    if (!bst)
        return NULL;
    else if (!bst->Left)
        return bst;
    else
        return findMin(bst->Left);
}
Position iterFindMax(BinTree bst)
{
    if (bst)
    {
        while (bst->Right)
            bst = bst->Right;
    }
    return bst;
}
Position insert(BinTree bst, ElementType x)
{
    if (!bst) //如果原树为空，生成并返回一个结点的二叉搜索树
    {
        bst = (BinTree)malloc(sizeof(struct TNode));
        bst->Data = x;
        bst->Left = bst->Right = NULL;
        return bst;
    }
    else
    {
        if (bst->Data < x)
        {
            bst->Right = insert(bst->Right, x); //递归插入右子树
        }
        else
        {
            bst->Left = insert(bst->Left, x); //递归插入左子树
        }
    }
    return bst;
}
BinTree delete (BinTree bst, ElementType x)
{
    BinTree tmp;
    if (!bst)
        printf("Not find node");
    else
    {
        if (x < bst->Data)
        {
            bst->Left = delete (bst->Left, x);
        }
        else if (x > bst->Data)
        {
            bst->Right = delete (bst->Right, x);
        }
        else
        {
            if (bst->Left && bst->Right) //被删除的结点有两个子结点
            {
                tmp = findMin(bst->Right); //在被删除结点的右子树中找到最小元素填充删除结点
                bst->Data = tmp->Data;
                bst->Right = delete (bst->Right, bst->Data); //删除被删除结点右子树的最小元素
            }
            else //只有一个子结点或无子结点
            {
                tmp = bst;
                if (!bst->Left)
                    bst = bst->Right;
                else if (!bst->Right)
                    bst = bst->Left;
                free(tmp);
            }
        }
    }
    return bst;
}