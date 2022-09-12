#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
int pre[N], in[N], post[N]; //分别存放前序、中序、后序遍历的结果
int stack[N];               //栈
int top = -1;

void post_traverse(int preL, int inL, int postL, int n);

int main()
{
    int n; //树的结点数
    scanf("%d", &n);

    char input[5];                 //每行的操作，push，pop，取最大长度4
    int preIndex = 0, InIndex = 0; //用来记录pre和in数组的下标
    for (int i = 0; i < 2 * n; i++)
    {
        scanf("%s", input);  // pop，还是push
        if (input[1] == 'u') // push
        {
            int num;
            scanf("%d", &num);     //输入要入栈的数
            pre[preIndex++] = num; //先序遍历
            stack[++top] = num;    //入栈
        }
        else // pop
        {
            in[InIndex++] = stack[top--]; //中序遍历
        }
    }
    post_traverse(0,0,0,n);
    for(int i=0;i<n-1;i++)
    {
        printf("%d ",post[i]);
    }
    printf("%d\n",post[n-1]);
    return 0;
}
void post_traverse(int preL, int inL, int postL, int n)
{
    if (n == 0)
        return;
    if (n == 1)
    {
        post[postL] = pre[preL];
        return;
    }

    int root = pre[preL];
    post[postL + n - 1] = root; //前序遍历的第一个元素就是后序遍历的最后一个元素
    int i;
    for (i = 0; i < n; i++) //找到root在中序遍历中的位置，root左边即左子树，右边及右子树，分而治之
    {
        if (in[inL+i] == root)
            break;
    }
    int leftNode = i;          //左边的结点个数
    int rightNode = n - i - 1; //右边的结点个数
    post_traverse(preL+1, inL, postL, leftNode);
    post_traverse(preL+leftNode+1,inL+leftNode+1,postL+leftNode,rightNode);
}