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

//图节点的定义
#define MAXV 100             //最大顶点数
#define INF 65535            //∞的大小
typedef char VertexDataType; //顶点的数据类型
struct MGNode
{
    int vNum;
    int eNum;
    WeightType edgeW[MAXV][MAXV]; //边权重值
    VertexDataType vData[MAXV];   //顶点的数据,如果顶点没有数据，则可以不定义
};
typedef struct MGNode *PtrToMGNode;
typedef PtrToMGNode MGraph;

/**
 * @brief 初始化一个有vNum个顶点，但没有边的图
 *
 * @param vNum
 * @return MGraph
 */
MGraph creatMGraph(int vNum)
{
    //初始化
    MGraph mG;
    mG = (MGraph)malloc(sizeof(struct MGNode));
    mG->eNum = 0;
    mG->vNum = vNum;

    //初始化边为无穷大，即无边
    for (int i = 0; i < vNum; i++)
    {
        for (int j = 0; j < vNum; j++)
        {
            mG->edgeW[i][j] = INF;
        }
    }

    return mG;
}

void insertEdge(MGraph mG, Edge e)
{
    mG->edgeW[e->v1][e->v2] = e->w;

    //如果为无向图，则还需执行下行语句
    mG->edgeW[e->v2][e->v1] = e->w;
}

MGraph buildGraph()
{
    MGraph mG;
    Edge e;
    int vNum;
    Vertex v;

    printf("enter the vertex number:\n");
    scanf("%d", &vNum);
    mG = creatMGraph(vNum);

    printf("enter the edge number:\n");
    scanf("%d", &(mG->eNum));
    if (mG->eNum != 0) //如果有边
    {
        e = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < mG->eNum; i++)
        {
            printf("enter the vertex1, vertex2 and the weight of edge:\n");
            scanf("%d %d %d", &(e->v1), &(e->v2), &(e->w));
            insertEdge(mG, e);
        }
    }

    //如果顶点有数据，则指向下面语句
    int flag;
    printf("is exist data of vertex?(yes:1 / no:0):\n");
    scanf("%d", &flag);
    if (flag)
    {
        for (int i = 0; i < mG->vNum; i++)
        {
            printf("enter data of vertex%d:\n", i);
            while (getchar() == '\n')
            {
                continue;
            }
            scanf("%c", &(mG->vData[i]));
        }
    }
    return mG;
}

int main()
{
    MGraph mG = buildGraph();
    return 0;
}
