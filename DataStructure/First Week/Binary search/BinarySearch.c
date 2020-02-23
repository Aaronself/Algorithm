/*
解题思路：
经典二分法，为了遍历所有的数据，记一下具体如何遍历所有的数据
具体记一下更新bottom和top的方式，都是在mid的基础上再增加和减少一位得到的
然后while的判断条件，可以使得遍历所有数据
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
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

//List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
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

/* 你的代码将被嵌在这里 */
Position BinarySearch(List L, ElementType X)
{
    int bottom, top, mid;

    bottom = 1;
    top = L->Last;
    mid = (bottom + top) / 2;

    while (bottom <= top)
    {
        if (L->Data[mid] > X)
            top = mid - 1;
        else if (L->Data[mid] < X)
            bottom = mid + 1;
        else if (L->Data[mid] == X)
            return mid;
        mid = (bottom + top) / 2;
    }
    return NotFound;
}
