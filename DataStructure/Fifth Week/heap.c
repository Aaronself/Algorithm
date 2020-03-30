/*
较为简单，注意创建的一个堆和插入的过程即可
*/#include <stdio.h>
#include <stdlib.h>
#define Min -10001

typedef struct HeapStruct *MinHeap;
struct HeapStruct{
    int *Heap;
    int Size;
    int Capacity;
};
MinHeap H;

MinHeap CreatHeap(int maxsize);
void InsertHeap(MinHeap H, int num);
void PrintPath(int N, int num);

int main()
{
    int i, j, N, M, path;
    int *list, *ptr;

    scanf("%d %d", &N, &M);
    H = CreatHeap(N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &j);
        InsertHeap(H, j);
    }

    list = (int *)malloc(M * sizeof(int));
    if(!list) return 0;
    ptr = list;
    for (i = 0; i < M; i++)
        scanf("%d", list++);
    for (i = 0; i < M; i++)
    {
        PrintPath(M, *ptr++);
        printf("\n");
    }
    return 0;
}

int IsFull (MinHeap H)
{
    if(H->Size == H->Capacity)
        return 1;

    return 0;
}

MinHeap CreatHeap(int maxsize)
{
    MinHeap H;
    
    H = (MinHeap)malloc(sizeof(struct HeapStruct));
    if(!H) return 0;
    H->Heap = (int *)malloc((maxsize + 1) * sizeof(int));
    if(!H->Heap)return 0;
    H->Size = 0;
    H->Capacity = maxsize;
    H->Heap[0] = Min;

    return H;
}
void InsertHeap(MinHeap H, int num)
{
    int i;
    if(IsFull(H))
        return 0;

    for (i = ++H->Size; H->Heap[i/2] > num; i /= 2)
        H->Heap[i] = H->Heap[i/2];
    H->Heap[i] = num;
}

void PrintPath(int N, int num)
{
    int i;

    printf("%d", H->Heap[num]);
    for (i = num / 2; i >= 1; i /= 2)
        printf(" %d", H->Heap[i]);
}
