/*
����˼·��
������ַ���Ϊ�˱������е����ݣ���һ�¾�����α������е�����
�����һ�¸���bottom��top�ķ�ʽ��������mid�Ļ����������Ӻͼ���һλ�õ���
Ȼ��while���ж�����������ʹ�ñ�����������
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode* List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* �������Ա������һ��Ԫ�ص�λ�� */
};

//List ReadInput(); /* ����ʵ�֣�ϸ�ڲ���Ԫ�ش��±�1��ʼ�洢 */
Position BinarySearch(List L, ElementType X);

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch(L, X);
    printf("%d\n", P);

    return 0;
}

/* ��Ĵ��뽫��Ƕ������ */
Position BinarySearch(List L, ElementType X)
{
    int bottom, top, mid, flag = 0;

    bottom = 1;
    top = L->Last;
    mid = (bottom + top) / 2;

    while (bottom < top)
    {
        if (L->Data[mid] > X)
            top = mid;
        else if (L->Data[mid] < X)
            bottom = mid;
        else if (L->Data[mid] == X)
        {
            flag = 1;

            return mid;
        }
        mid = (bottom + top) / 2;
    }
    if (flag == 0)
        return NotFound;
}