/*
解题思路：
计算每个工序的最短工期比较简单，正向拓扑排序即可
为了计算关键步骤还需要计算最晚开始时间，需要节点的出度和对序列做反向拓扑排序
为了实现输出的要求，需要对节点的空余时间进行计算
计算的时候要考虑到多入口多出口的情况。在多出口的情况时，
出口的最晚开始时间应该被设置为整个工序的最短完成时，然后再次计算ManeuverTime空余时间
然后根据题目需求反向输出即可
*/
#include <stdio.h>
#include <malloc.h>
#define Maxsize 102
#define MAX 32767
#define Null -1

struct QueneNode{
    int list[Maxsize];
    int rear;
    int front;
    int maxsize;
};
typedef struct QueneNode *Quene;

int ActiveNode[Maxsize][Maxsize];
int Indegree[Maxsize] = { 0 };
int Outdegree[Maxsize] = { 0 };
int EarliestComplete[Maxsize] = { 0 };
int LastBegin[Maxsize] = { 0 };
int ManeuverTime[Maxsize] = { 0 };

int TopSort(Quene Q, int N);
void EaristTime(int N);
void KeyActive();
Quene CreatQuene(int N);
int IsEmpty(Quene Q);
void Enquene(Quene Q, int N);
int Dequene(Quene Q);
int Maxnum(int a, int b);
int Minnum(int a, int b);

int main()
{
    int i, j, k, l;
    int N, M, cnt;
    Quene Q;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            ActiveNode[i][j] = MAX;
    }

    Q = CreatQuene(N);
    for (i = 0; i < M; i++)
    {
        scanf("%d %d %d", &j, &k, &l);
        /* 此图为有向图 */
        ActiveNode[j][k] = l;
        Indegree[k]++;
        Outdegree[j]++;
    }

    cnt = TopSort(Q, N);
    EaristTime(cnt);
    KeyActive(cnt);
}

int TopSort(Quene Q, int N)
{
    int i, j;
    int tmp = 0, cnt = 0;
    //int list[Maxsize] = {0};

    for (i = 1; i <= N; i++)
    {
        if(Indegree[i] == 0)
            Enquene(Q, i);
    }
    
    while(!IsEmpty(Q))
    {
        /* 队列中的顶点的入度皆为0 */
        tmp = Dequene(Q);
        cnt++;
        /* printf tmp */
        for (j = 1; j <= N; j++)
        {
            /* 找tmp的邻接点 */
            if(ActiveNode[tmp][j] != MAX)
            {
                Indegree[j]--;
                EarliestComplete[j] = Maxnum(EarliestComplete[j], EarliestComplete[tmp] + ActiveNode[tmp][j]);
                if(Indegree[j] == 0)
                    Enquene(Q, j);
            }
        }
    }

    if(cnt < N)
    {
        printf("0");
        return 0;
    }

    return cnt;
}

void EaristTime(int N)
{
    int i, tmp, max=0;

    if(N == 0) return;
    for (i = 1; i <= N; i++)
    {
        tmp = EarliestComplete[i];
        if(tmp > max) max = tmp;
    }
    printf("%d", max);
}

void KeyActive(int N)
{
    int i, j, tmp, max = 0;
    Quene Q;

    Q = CreatQuene(N);

    for (i = 1; i <= N; i++)
    {
        tmp = EarliestComplete[i];
        if(tmp > max) max = tmp;
    }

    for (i = 1; i <= N; i++)
    {
        if(Outdegree[i] == 0)
        {
            LastBegin[i] = max;
            Enquene(Q, i);
        }
        else
            LastBegin[i] = MAX;
    }

    while(!IsEmpty(Q))
    {
        tmp = Dequene(Q);
        for (j = 1; j <= N; j++)
        {
            if(ActiveNode[j][tmp] != MAX)
            {   
                LastBegin[j] = Minnum(LastBegin[j], LastBegin[tmp]-ActiveNode[j][tmp]);
                Outdegree[j]--;
                if(Outdegree[j] == 0)
                    Enquene(Q, j);
            }
        }
    }
    /* 出度为0的点，更新一下最后开始时间为最长完工时间，即终点的Last为最长完工时间 */
    // for (i = 0; i < index; i++)
    //     LastBegin[list[i]] = max;
        /* 计算机动时间 */
    for (i = 1; i <= N; i++)
        ManeuverTime[i] = LastBegin[i] - EarliestComplete[i];

    for (i = 1; i <= N; i++)
    {
        if(ManeuverTime[i] == 0)
        {
            for (j = N; j >= 1; j--)
            {
                if(ActiveNode[i][j] != MAX && LastBegin[j] - EarliestComplete[i] - ActiveNode[i][j] == 0)
                {
                    printf("\n%d->%d", i, j);
                }
            }
        }
    }
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

int Maxnum(int a, int b)
{
    return a >= b ? a : b;
}

int Minnum(int a, int b)
{
    return a <= b ? a : b;
}