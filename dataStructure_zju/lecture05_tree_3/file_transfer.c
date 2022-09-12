#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXSIZE 10000

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAXSIZE];

SetName find(SetType set, ElementType x)
{
    if (set[x] < 0)
        return x;
    else
        return set[x] = find(set, set[x]);
}
void unioSet(SetType set, SetName r1, SetName r2)
{
    if (set[r1] > set[r2]) // r2高
    {
        set[r2] += set[r1];
        set[r1] = r2; // r1指向r2
    }
    else // r1高
    {
        set[r1] += set[r2];
        set[r2] = r1; // r2指向r1
    }
}
void init(SetType set, int n)
{
    for (int i = 0; i < n; i++)
        set[i] = -1;
}
void inputConnection(SetType set)
{
    ElementType x, y;
    SetName r1, r2;
    scanf("%d %d", &x, &y);
    r1 = find(set, x - 1);
    r2 = find(set, y - 1);
    if (r1 != r2)
        unioSet(set, r1, r2);
}
void checkConnection(SetType set)
{
    ElementType x, y;
    SetName r1, r2;
    scanf("%d %d", &x, &y);
    r1 = find(set, x - 1);
    r2 = find(set, y - 1);
    if (r1 == r2)
        printf("yes\n");
    else
        printf("no\n");
}
void checkNetwork(SetType set, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (set[i] < 0)
            count++;
    }
    if (count == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", count);
}
int main()
{
    //初始化指令集
    SetType set;
    int n;
    char in;
    scanf("%d", &n);
    init(set, n);
    do
    {
        scanf("%c", &in);
        switch (in)
        {
        case 'I':
            inputConnection(set);
            break;
        case 'C':
            checkConnection(set);
            break;
        case 'S':
            checkNetwork(set, n);
        default:
            break;
        }
    } while (in != 'S');
    return 0;
}
