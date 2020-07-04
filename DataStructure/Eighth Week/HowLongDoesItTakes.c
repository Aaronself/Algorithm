/*
解题思路：
先完成拓扑排序
拓扑排序：有点类似Dijkstra算法，同样是利用了队列完成的遍历。
可以理解为收录进队列中的点，它的最长时间已经确定好了，类比为Dijkstra算法中的，收录进的点，最短路径已经确定
然后再构建一个数组LongestComplete即可记录每个点的最长完成时间，最后挑选出最大的那个即为整个工序的最长时间。
*/

#include <stdio.h>
#include <malloc.h>
#define Maxsize 100
#define Null -1
#define MAX 32767
#define Null -1

struct QueneNode{
    int list[Maxsize];
    int rear;
    int front;
    int maxsize;
};
typedef struct QueneNode *Quene;

int Maxnum(int a, int b);
int ActiveNode[Maxsize][Maxsize];
int Indegree[Maxsize] = { 0 };
int EarliestComplete[Maxsize] = { Null };
int LongestComplete[Maxsize] = { 0 };

void TopSort(Quene Q, int N);
Quene CreatQuene(int N);
int IsEmpty(Quene Q);
void Enquene(Quene Q, int N);
int Dequene(Quene Q);

int main()
{
    int i, j, k, l;
    int N, M;
    Quene Q;

    scanf("%d %d", &N, &M);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            ActiveNode[i][j] = MAX;
    }

    Q = CreatQuene(N);
    for (i = 0; i < M; i++)
    {
        scanf("%d %d %d", &j, &k, &l);
        /* 此图为有向图 */
        ActiveNode[j][k] = l;
        Indegree[k]++;
    }

    TopSort(Q, N);
}

void TopSort(Quene Q, int N)
{
    int i, j;
    int tmp = 0, cnt = 0, max;
    //int list[Maxsize] = {0};

    for (i = 0; i < N; i++)
    {
        if(Indegree[i] == 0)
            Enquene(Q, i);
    }
    
    while(!IsEmpty(Q))
    {
        /* 队列中的顶点的入度皆为0 */
        tmp = Dequene(Q);
        /*list[cnt++] = tmp;*/
        cnt++;
        /* printf tmp */
        for (j = 0; j < N; j++)
        {
            /* 找tmp的邻接点 */
            if(ActiveNode[tmp][j] != MAX)
            {
                Indegree[j]--;
                LongestComplete[j] = Maxnum(LongestComplete[j], LongestComplete[tmp] + ActiveNode[tmp][j]);
                if(Indegree[j] == 0)
                    Enquene(Q, j);
            }
        }
    }

    if(cnt < N)
    {
        printf("Impossible\n");
        return;
    }
    else
    {
        max = 0;
        for (i = 0; i < cnt; i++)
        {
            tmp = LongestComplete[i];
            if(tmp > max) max = tmp;
        }
        printf("%d", max);
    }
}

int Maxnum(int a, int b)
{
    return a >= b ? a : b;
}

Quene CreatQuene(int N)
{
    int i;
    Quene Q;

    Q = malloc(sizeof(struct QueneNode));
    for (i = 0; i < N; i++)
        Q->list[i] = 0;
    Q->rear = Q->front = 0;
    Q->maxsize = N;

    return Q;
}

int IsEmpty(Quene Q)
{
    if(Q->front == Q->rear)
        return 1;
    else
        return 0;
}

void Enquene(Quene Q, int N)
{
    Q->rear = (Q->rear + 1) % Q->maxsize;
    Q->list[Q->rear] = N;
}

int Dequene(Quene Q)
{
    if(!IsEmpty(Q))
    {
        Q->front = (Q->front + 1) % Q->maxsize;
        return Q->list[Q->front];
    }
    else
        return Null;
}