#include <stdio.h>
typedef int ElementType;
typedef struct GNode *GList;
struct GNode
{
    int tag;//0表示单元素；1表示结点是广义表
    union URegion{
        ElementType Data;
        GList SubList;
    };  
    GList Next;
};
