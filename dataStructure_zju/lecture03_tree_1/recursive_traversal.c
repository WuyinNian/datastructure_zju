#include <stdio.h>
typedef int ElementType; //树结点储存的类型
typedef struct TNode *Position;
typedef Position BinTree; /* 二叉树类型 */
struct TNode
{                     /* 树结点定义 */
    ElementType Data; /* 结点数据 */
    BinTree Left;     /* 指向左子树 */
    BinTree Right;    /* 指向右子树 */
};

//先序遍历
void PreOrderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}
//中序遍历
void InOrderTraversal(BinTree BT)
{
    if (BT)
    {
        PreOrderTraversal(BT->Left);
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Right);
    }
}
//后序遍历
void PostOrderTraversal(BinTree BT)
{
    if (BT)
    {
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
        printf("%d", BT->Data);
    }
}
//求树的深度
int postOrderTraversal(BinTree binT)
{
    int leftH, rightH, maxH;
    if(binT)
    {
        leftH = postOrderTraversal(binT->Left);//求左子树的深度
        rightH = postOrderTraversal(binT->Right);//求右子树的深度
        maxH = (leftH > rightH) ? leftH : rightH;//取左右子树的较大的深度
        return (maxH + 1);
    }
    else    
        return 0;//空树深度为0
}