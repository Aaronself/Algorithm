#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 10000

typedef struct Node *PtrToNode;
struct Node {
    int key;
    PtrToNode next;
};

PtrToNode Std[MAXSIZE] = {NULL};
int main()
{
    int i, N, K, M;
    int stdID, class, score;

    scanf("%d %d %d", &N, &K, &M);
    for (i = 0; i < M; i++)
    {
        scanf(" %d %d %d", stdID, class, score);

    }
}