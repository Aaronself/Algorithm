/*
解题思路：
链表的一个基本操作，合并链表
题目的亮点：
1.L1和L2是带有头节点的单链表 
2.在合并的时候，使用原序列的节点而非自己创造
解题亮点：
合并的时候，当合并完L1或L2时，采用的? : 语句，减少了大量的工作
多熟悉链表操作
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Merge(List L1, List L2);
List ReadPoly();
//List Read(); /* 细节在此不表 */
//void Print(List L); /* 细节在此不表；空链表将输出NULL */
void Print(List L);
int main()
{
    List L1, L2, L;
    L1 = ReadPoly();
    L2 = ReadPoly();
    L = Merge(L1, L2);
    Print(L->Next);
    return 0;
}

void Print(List L)
{
    while (L)
    {
        printf("%d ", L->Data);
        L = L->Next;
    }
}

List ReadPoly()
{
    int i, c, N;
    List P, rear, t, tmp;

    P = (List)malloc(sizeof(struct Node));
    if (P == NULL) return 0;
    P->Next = NULL;
    rear = P;

    scanf_s("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf_s("%d", &c);
        tmp = (List)malloc(sizeof(struct Node));
        if (!tmp)return 0;
        tmp->Data = c;
        tmp->Next = NULL;
        rear->Next = tmp;
        rear = tmp;
    }

    return P;
}


/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2)
{
    List P, rear, t1, t2;

    P = (List)malloc(sizeof(struct Node));
    if (!P)return 0;
    P->Next = NULL;
    rear = P;

    if (!L1 && !L2) return P->Next;
    else if (!L1 || !L2) return 0;
    t1 = L1->Next; 
    t2 = L2->Next;
    while (t1 && t2)
    {
        if (t1->Data <= t2->Data)
        {
            rear->Next = t1;
            rear = t1;
            t1 = t1->Next;
        }
        else if (t2->Data < t1->Data)
        {
            rear->Next = t2;
            rear = t2;
            t2 = t2->Next;
        }
    }

    rear->Next = t1 ? t1 : t2;

    L1->Next = NULL;
    L2->Next = NULL;

    return P;
}