#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//边的定义
typedef int Vertex;     //用定点下标来表示顶点
typedef int WeightType; //边的权值类型
struct ENode
{
    Vertex v1, v2;
    WeightType w;
};
typedef struct ENode *PtrToENode;
typedef PtrToENode Edge;

//邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex vIndex; //邻接点下标
    WeightType edgeW;
    PtrToAdjVNode next;
};

//顶点表头结点的设置
#define MaxV 100
typedef char VertexDataType;
typedef struct VNode
{
    PtrToAdjVNode firstAdjVN;
    VertexDataType data;
} AdjVList[MaxV];

//图结点的定义
struct TGNode
{
    int vNum;
    int eNum;
    AdjVList vList;
};
typedef struct TGNode *PtrToTGNode;
typedef PtrToTGNode TGraph;

TGraph creatTGraph(int vNum)
{
    TGraph tG = (TGraph)malloc(sizeof(struct TGNode));
    tG->vNum = vNum;
    tG->eNum = 0;
    for (int i = 0; i < vNum; i++)
    {
        tG->vList[i].firstAdjVN = NULL;
    }
    return tG;
}

void insertEdge(TGraph tG, Edge e)
{
    //建立v2邻接点
    PtrToAdjVNode newNode;
    newNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    newNode->vIndex = e->v2;
    newNode->edgeW = e->w;
    // v2插入v1表头，即vList[v1]
    newNode->next = tG->vList[e->v1].firstAdjVN;
    tG->vList[e->v1].firstAdjVN = newNode;

    //如果是无向图则还需将v1插入v2表头
    newNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    newNode->vIndex = e->v1;
    newNode->edgeW = e->w;
    // v2插入v1表头，即vList[v1]
    newNode->next = tG->vList[e->v2].firstAdjVN;
    tG->vList[e->v2].firstAdjVN = newNode;
}

TGraph buildTGraph()
{
    TGraph tG;
    printf("enter vertex numbers:\n");
    int vNum;
    scanf("%d", &vNum);
    tG = creatTGraph(vNum);

    printf("enter edge numbers\n");
    scanf("%d", &(tG->eNum));
    Edge e;
    for (int i = 0; i < tG->eNum; i++)
    {
        e = (Edge)malloc(sizeof(struct ENode));
        printf("enter vertex1, vertex2 and weight:\n");
        scanf("%d %d %d", &e->v1, &e->v2, &e->w);
        insertEdge(tG, e);
    }

    //如果顶点有数据，则指向下面语句
    int flag;
    printf("is exist data of vertex?(yes:1 / no:0):\n");
    scanf("%d", &flag);
    if (flag)
    {
        for (int i = 0; i < tG->vNum; i++)
        {
            printf("enter data of vertex%d:\n", i);
            while (getchar() == '\n')
            {
                continue;
            }

            scanf("%c", &(tG->vList[i].data));
        }
    }
    return tG;
}

int main()
{
    TGraph tG = buildTGraph();
    return 0;
}