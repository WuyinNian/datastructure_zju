#include <stdio.h>
#include <stdlib.h>

//搜索树的表示
typedef struct TNode *Tree;
struct TNode
{
    int v;
    Tree left, right;
    int flag; //判别一个序列是否和树一致，访问过：0 访问过：1
};

Tree makeTree(int n);
int judge(Tree t, int n);
void resetTree(Tree t);
void freeTree(Tree t);

int main()
{
    int n, l;
    Tree t;
    scanf("%d", &n); //读取序列的结点数
    while (n)
    {
        scanf("%d", &l); //输入需要比较的序列数
        t = makeTree(n); //构建被比较的树
        for (int i = 0; i < l; i++)
        {
            if (judge(t, n)) //判段是否是同一棵树
                printf("Yes\n");
            else
                printf("No\n");
            resetTree(t); //重置t中的flag
        }
        freeTree(t); //释放t的空间
        scanf("%d", &n);
    }
    return 0;
}

Tree newNode(int v)
{
    Tree t = (Tree)malloc(sizeof(struct TNode));
    t->v = v;
    t->left = t->right = NULL;
    t->flag = 0;
    return t;
}
Tree insert(Tree t, int v)
{
    if (!t) // t是空树
        t = newNode(v);
    else
    {
        if (v < t->v)
            t->left = insert(t->left, v);
        else if (v > t->v)
            t->right = insert(t->right, v);
    }
    return t;
}
Tree makeTree(int n)
{
    Tree t;
    int v;
    scanf("%d", &v);
    t = newNode(v); //构建根结点;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &v);  //读取序列元素
        t = insert(t, v); //插入新结点
    }
    return t;
}

int check(Tree t, int v)
{
    if (t->flag) //已经被访问过
    {
        if (v < t->v)
            return check(t->left, v);
        else if (v > t->v)
            return check(t->right, v);
        else //如果相等，表明待判断序列中的整数出现了两次以上
            return 0;
    }
    else //未被访问过
    {
        if (v == t->v) //正好是要找的结点，flag设置为1
        {
            t->flag = 1;
            return 1;
        }
        else //碰见一个以前没见过的结点
            return 0;
    }
}
int judge(Tree t, int n)
{
    //当发现不一致时，必须读完该序列的所有数，才能return，否则会干扰下一序列的判断
    //因此flag用来标记该序列是否与树一致,flag=1:遇到未出现过的结点，该序列与树不一致
    int v, flag = 0;
    scanf("%d", &v);
    if (v != t->v)
        flag = 1;
    else
        t->flag = 1;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &v);
        if ((!flag) && (!check(t, v)))
            flag = 1;
    }
    return !flag;
}

void resetTree(Tree t)
{
    if (t->left)
        resetTree(t->left);
    if (t->right)
        resetTree(t->right);
    t->flag = 0;
}

void freeTree(Tree t)
{
    if (t->left)
        freeTree(t->left);
    if (t->right)
        freeTree(t->right);
    free(t);
}