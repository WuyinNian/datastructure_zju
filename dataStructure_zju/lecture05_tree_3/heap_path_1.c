#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 1001
#define MINH -10001
int H[MAXN], size;
void creat()
{
    size = 0;
    H[0] = MINH;
}

void insert(int x)
{
    if (size == MAXN)
        return;
    int i;
    for (i = ++size; H[i / 2] > x; i /= 2)
        H[i] = H[i / 2];
    H[i] = x;
}

int main()
{
    int n, k, x, index;
    scanf("%d %d", &n, &k);
    creat();
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        insert(x);
    }
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &index);
        printf("%d", H[index]);
        while (index > 1)
        {
            index /= 2;
            printf(" %d", H[index]);
        }
        printf("\n");
    }
    return 0;
}