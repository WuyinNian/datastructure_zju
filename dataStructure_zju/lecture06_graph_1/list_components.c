#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 10

int vNum, eNum;
int g[MAX][MAX];
bool dfsVisited[MAX];
bool bfsVisited[MAX];

void dfs(int v)
{
    dfsVisited[v] = true;
    printf(" %d", v);
    for (int i = 0; i < vNum; i++)
    {
        if (g[v][i] && !dfsVisited[i])
            dfs(i);
    }
}

void bfs(int v)
{
    bfsVisited[v] = true;
    int q[MAX], back = -1, front = -1;
    q[++back] = v;
    while (back != front)
    {
        int temp = q[++front];
        printf(" %d", temp);
        for (int i = 0; i < vNum; i++)
        {
            if (g[temp][i] && !bfsVisited[i])
            {
                bfsVisited[i] = true;
                q[++back] = i;
            }
        }
    }
}

int main()
{
    // 1. 输入顶点个数和边数
    scanf("%d %d", &vNum, &eNum);

    // 2.用矩阵表示图,并创建连通的边
    int i, j;
    while (eNum)
    {
        scanf("%d %d", &i, &j);
        g[i][j] = 1;
        g[j][i] = 1;
        eNum--;
    }

    // 3.dfs
    for (int i = 0; i < vNum; i++)
    {
        if (!dfsVisited[i])
        {
            putchar('{');
            dfs(i);
            printf(" }\n");
        }
    }

    // 4.bfs
    for (int i = 0; i < vNum; i++)
    {
        if (!bfsVisited[i])
        {
            putchar('{');
            bfs(i);
            printf(" }\n");
        }
    }
}