#include <stdio.h>
#include <stdlib.h>

struct PolyNode
{
    int expon;
    int coef;
    struct PolyNode *Next;
};
typedef struct PolyNode *Polynomial;

void Attach(int coef, int expon, Polynomial *rear) //需要修改rear指针的值，所以传入指向rear指针的指针
{
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = coef;
    P->expon = expon;
    P->Next = NULL;
    (*rear)->Next = P;
    (*rear) = P;
}

Polynomial ReadPoly()
{
    Polynomial front, rear, temp;
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    rear->Next = NULL;
    front = rear;
    int coef, expon, N;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d %d", &coef, &expon);
        Attach(coef, expon, &rear);
    }
    temp = front;
    front = front->Next;
    free(temp);
    return front;
}

Polynomial MultPoly(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear, temp, t1, t2;
    if (!P2 || !P1)
        return NULL;
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    rear->Next = NULL;
    front = rear;
    t1 = P1;
    t2 = P2;
    while (t2)
    {
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &rear);
        t2 = t2->Next;
    }
    t1 = t1->Next;
    int coef, expon;
    while (t1)
    {
        t2 = P2;
        rear = front;
        while (t2)
        {
            coef = t1->coef * t2->coef;
            expon = t1->expon + t2->expon;
            while (rear->Next && rear->Next->expon > expon)//必须先判断rear->Next是否为空，否则会报Segmentation fault: 11
            {
                rear = rear->Next;
            }
            if (rear->Next && rear->Next->expon == expon)//
            {
                if (coef + rear->Next->coef)
                {
                    rear->Next->coef += coef;
                }
                else
                {
                    temp = rear->Next;
                    rear->Next = temp->Next;
                    free(temp);
                }
            }
            else
            {
                temp = (Polynomial)malloc(sizeof(struct PolyNode));
                temp->coef = coef;
                temp->expon = expon;
                temp->Next = rear->Next;
                rear->Next = temp;
                rear = rear->Next;
            }
            t2 = t2->Next;
        }
        t1 = t1->Next;
    }
    t2 = front;
    front = front->Next;
    free(t2);
    return front;
}

int Compare(int a, int b)
{
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else
        return 0;
}

Polynomial AddPoly(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear;
    rear = (Polynomial)malloc(sizeof(struct PolyNode)); //为插入方便，插入临时空结点
    rear->Next = NULL;
    front = rear;
    int coefSum;
    while (P1 && P2)
    {
        switch (Compare(P1->expon, P2->expon))
        {
        case 1:
            Attach(P1->coef, P1->expon, &rear);
            P1 = P1->Next;
            break;
        case -1:
            Attach(P2->coef, P2->expon, &rear);
            P2 = P2->Next;
            break;
        case 0:
            coefSum = P1->coef + P2->coef;
            if (coefSum)
                Attach(coefSum, P1->expon, &rear);
            P1 = P1->Next;
            P2 = P2->Next;
            break;
        }
    }
    for (; P1; P1 = P1->Next)
        Attach(P1->coef, P1->expon, &rear);
    for (; P2; P2 = P2->Next)
        Attach(P2->coef, P2->expon, &rear);
    Polynomial temp = front;
    front = front->Next;
    free(temp);
    return front;
}

void PrintPoly(Polynomial P)
{
    int flag = 0;
    if (!P)
    {
        printf("0 0\n");
        return;
    }
    while (P)
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d", P->coef, P->expon);
        P = P->Next;
    }
    printf("\n");
}

int main()
{
    Polynomial P1, P2, multP, addP;
    P1 = ReadPoly();
    P2 = ReadPoly();
    multP = MultPoly(P1, P2);
    addP = AddPoly(P1, P2);
    PrintPoly(multP);
    PrintPoly(addP);
    return 0;
}