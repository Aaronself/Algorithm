/*
����˼·��
�����һ�������������ϲ�����
��Ŀ�����㣺
1.L1��L2�Ǵ���ͷ�ڵ�ĵ����� 
2.�ںϲ���ʱ��ʹ��ԭ���еĽڵ�����Լ�����
�������㣺
�ϲ���ʱ�򣬵��ϲ���L1��L2ʱ�����õ�? : ��䣬�����˴����Ĺ���
����Ϥ�������
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
//List Read(); /* ϸ���ڴ˲��� */
//void Print(List L); /* ϸ���ڴ˲������������NULL */
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


/* ��Ĵ��뽫��Ƕ������ */
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