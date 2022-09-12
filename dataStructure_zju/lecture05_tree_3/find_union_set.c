#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXSIZE 1000

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