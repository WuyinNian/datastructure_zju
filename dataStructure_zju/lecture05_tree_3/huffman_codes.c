#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    int weight;
    char c;
    HuffmanTree left, right;
};

typedef HuffmanTree ElementType;
typedef struct HNode *Heap;
struct HNode
{
    ElementType *data; //储存元素的数组
    int size;          //堆中当前元素的个数
    int capacity;      //堆的容量
};
typedef Heap MinHeap;
#define MINDATA -1000; //该值应根据具体情况定义为小于堆中所有可能元素的值

MinHeap creatHeap(int maxSize)
{
    MinHeap minH = (MinHeap)malloc(sizeof(struct HNode));
    minH->data = (ElementType *)malloc(sizeof(struct TreeNode *) * maxSize + 1);
    minH->data[0] = (ElementType)malloc(sizeof(struct TreeNode));
    minH->data[0]->weight = MINDATA; //定义哨兵为小于堆中所有可能的最小值
    minH->size = 0;
    minH->capacity = maxSize;
    return minH;
}
int isFull(MinHeap minH)
{
    return minH->capacity == minH->size;
}
bool insert(MinHeap minH, ElementType x)
{
    if (isFull(minH))
    {
        printf("heap full\n");
        return false;
    }
    int i = ++minH->size; // i指向插入堆后的最后一个位置
    //将堆的最小值下沉
    // data[0]为哨兵元素，控制循环结束
    for (; minH->data[i / 2]->weight > x->weight; i /= 2)
    {
        minH->data[i] = minH->data[i / 2];
    }
    minH->data[i] = x; //插入
    return true;
}
int isEmpty(MinHeap minH)
{
    return minH->size == 0;
}

ElementType deleteMin(MinHeap minH)
{
    if (isEmpty(minH))
    {
        printf("heap empty\n");
        return NULL;
    }
    int parent, child;
    ElementType minItem, temp;
    minItem = minH->data[1];         //取出最小值
    temp = minH->data[minH->size--]; //保存堆的最后一个元素，准备找到合适的位置存放
    for (parent = 1; 2 * parent <= minH->size; parent = child)
    {
        child = 2 * parent;                                                                   //指向左儿子
        if (child != minH->size && minH->data[child]->weight > minH->data[child + 1]->weight) //判断左儿子是否是最后一个元素 并且找出最小的儿子
            child++;
        if (temp->weight <= minH->data[child]->weight) //要放置的元素如果小于最小的儿子，说明该parent是该元素要放置的位置
            break;
        else //要放置的元素大于于最小的儿子，parent位置元素替换为child位置元素，parent指向child
            minH->data[parent] = minH->data[child];
    }
    minH->data[parent] = temp;
    return minItem;
}
void filterDown(MinHeap minH, int p)
{
    if (isEmpty(minH))
    {
        printf("heap empty!\n");
        return;
    }
    int parent, child;
    ElementType temp = minH->data[p];
    for (parent = p; parent * 2 <= minH->size; parent = child)
    {
        child = parent * 2;
        if (child != minH->size && minH->data[child]->weight > minH->data[child + 1]->weight) //找出最大频率（权重）最大的子结点
        {
            child++;
        }
        if (temp->weight <= minH->data[child]->weight) //必须等号，否则相等情况下，二者位置会调换
            break;
        else
            minH->data[parent] = minH->data[child];
    }
    minH->data[parent] = temp;
}
void buildMinHeap(MinHeap minH)
{
    for (int i = minH->size / 2; i > 0; i--)
        filterDown(minH, i);
}

HuffmanTree creatHuffmanTree(MinHeap minH)
{
    //假设权值已经储存在minH->data[i]->weight中
    HuffmanTree huffmanT;
    buildMinHeap(minH);
    for (int i = 1; i < minH->capacity; i++) //这边必须用capacity，因为size会随delete改变
    {
        huffmanT = (HuffmanTree)malloc(sizeof(struct TreeNode));
        huffmanT->left = deleteMin(minH);
        huffmanT->right = deleteMin(minH);
        huffmanT->weight = huffmanT->left->weight + huffmanT->right->weight;
        insert(minH, huffmanT);
    }
    huffmanT = deleteMin(minH);
    return huffmanT;
}
/*************以上为构建huffman树的代码****************/

#define N 65
#define M 1000

int f[N];
// n: 需要编码的字符数量
void readData(MinHeap mH, int n);

// depth：当前结点的树的深度
int WPL(HuffmanTree huffTree, int depth);

int main()
{
    // 1.读入需要编码的字符数n
    int n;
    scanf("%d", &n);

    // 2.创建一个最小堆读取每个需要编码的字符及其频率（权重）存入堆中的数组，并创建哈夫曼树
    //数组类型是哈夫曼树结点，结点的属性包含字符和权重,
    MinHeap mH = creatHeap(n);
    readData(mH, n);
    HuffmanTree huffTree = creatHuffmanTree(mH);

    // 3.计算最优编码长度
    int bestCodeLen = WPL(huffTree, 0);

    // 4.读取需要检查的编码数量,并检查长度是否正确
    int m;
    scanf("%d", &m);
    char code[n]; //存储字符的编码
    //根据编码创建树
    for (int i = 0; i < m; i++) //遍历每个学生
    {
        char ch;                                                              //存储每行编码所属的字符
        HuffmanTree checkTree = (HuffmanTree)malloc(sizeof(struct TreeNode)); //每一学生都需要创建一颗新树
        checkTree->weight = MINDATA;
        HuffmanTree tmp;
        bool flag = false;          //建树过程中用以标识是否含有前缀码
        int codeLen = 0;            //记录编码长度
        int strLen;
        for (int j = 0; j < n; j++) //遍历一个学生的七个字符的编码
        {
            getchar();                 //清除缓存区的字符
            scanf("%c %s", &ch, code); //输入字符及其编码
            strLen = strlen(code);
            if (strLen > n)
            {
                flag = true;
                break;
            }
            tmp = checkTree;
            for (int k = 0; k < strLen; k++) //遍历code
            {
                if (code[k] == '0') //如果编码为0，考虑左子结点
                {
                    if (!tmp->left) //左子结点不存在，向左插入新结点
                    {
                        HuffmanTree newNode = (HuffmanTree)malloc(sizeof(struct TreeNode));
                        tmp->left = newNode;
                        tmp = newNode;
                    }
                    else //左子结点存在
                    {
                        tmp = tmp->left;
                        if (tmp->c != '\0') //如果左子结点的字符不为空，说明是叶子结点，那么这一段编码为前缀码
                        {
                            flag = true;
                        }
                    }
                }
                else if (code[k] == '1') //如果编码为1，考虑右子结点
                {
                    if (!tmp->right) //右子结点不存在，向右插入新结点
                    {
                        HuffmanTree newNode = (HuffmanTree)malloc(sizeof(struct TreeNode));
                        tmp->right = newNode;
                        tmp = newNode;
                    }
                    else //右子结点存在
                    {
                        tmp = tmp->right;
                        if (tmp->c != '\0') //如果右子结点的字符不为空，说明是叶子结点，那么这一段编码为前缀码
                        {
                            flag = true;
                        }
                    }
                }
            }
            //一段code遍历结束后，判断当前的tmp是否是叶子结点，如果是则该编码不是前缀码
            //如果不是，则该编码是前缀码
            if (!tmp->left && !tmp->right)
            {
                tmp->c = ch;
                tmp->weight = f[j];
                codeLen += (f[j] * strlen(code));
            }
            else
            {
                flag = true;
            }
        }
        if (flag == true || codeLen != bestCodeLen) //检查是否含前缀码及长度是否正确
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
        }
    }
    return 0;
}

void readData(MinHeap mH, int n)
{
    char ch;
    int fr;
    for (int i = 0; i < n; i++)
    {
        getchar(); //输出缓存区的空格
        scanf("%c %d", &ch, &fr);
        HuffmanTree newNode = (HuffmanTree)malloc(sizeof(struct TreeNode));
        newNode->weight = fr;
        f[i] = fr;
        newNode->c = ch;
        insert(mH, newNode);
    }
}

int WPL(HuffmanTree huffTree, int depth)
{
    //如果是叶子结点，返回当前结点的深度乘上权重
    if (!huffTree->left && !huffTree->right)
        return huffTree->weight * depth;
    else //非叶子结点，递归左右子结点WPL
        return WPL(huffTree->left, depth + 1) + WPL(huffTree->right, depth + 1);
}