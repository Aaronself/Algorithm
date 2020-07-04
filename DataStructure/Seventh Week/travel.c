/*
解题思路：
旅游规划：
此题为一个带有双权重的Dijkstra问题
问题中，有两个权重，一个是路径的长度，为第一优先级，另外一个是路径的开销，为第二优先级
算法只需在原有的Dijkstra算法上做一定的修改即可。
修改时，判断路径长度短的更新，若路径长度相同，则采用cost的比较方案，采取开销更小的路径
Dijkstra该算法的实质即：认为已经 collected 集合中的点的最小路径已经确定，现在对这个集合的邻接点做辐射的路径计算
集合外的点可以与集合中的点有多个重合点，根据迭代后，找到最优解，当将其收入 collected 集合后，从起始点到该点的路径也已经确定了
*/

#include <stdio.h>
#define MAX 32768
#define MaxSize 500

void Init(int N);
void InsertEdge(int start, int end, int time, int cost);
void Dijkstra(int start, int end, int N);

int citylist[MaxSize][MaxSize];
int citytime[MaxSize][MaxSize];
int citycost[MaxSize][MaxSize];
int collected[MaxSize] = {0};
int Mindist[MaxSize] = {MAX};

int main()
{
    int i, j, k, m, n;
    int N, M, start, end;

    scanf("%d %d %d %d", &N, &M, &start, &end);
    Init(N);
    for (i = 0; i < M; i++)
    {
        scanf("%d %d %d %d", &j, &k, &m, &n);
        InsertEdge(j, k, m, n);
    }

    /* Dijkstra算法开始前先完成初始化 */
    for (i = 0; i < N; i++)
    {
        if(citylist[i][start] == 1)
            Mindist[i] = citytime[i][start];
    }
    collected[start] = 0;
    Dijkstra(start, end, N);
    printf("%d %d", Mindist[end], citycost[end][start]);
}
void Init(int N)
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        Mindist[i] = MAX;
        collected[i] = 0;
        for (j = 0; j < N; j++)
        {
            citylist[i][j] = MAX;
            citytime[i][j] = 0;
            citycost[i][j] = 0;
        }
    }
}
void InsertEdge(int start, int end, int time, int cost)
{
    citylist[start][end] = 1;
    citylist[end][start] = 1;
    citytime[start][end] = time;
    citytime[end][start] = time;
    citycost[start][end] = cost;
    citycost[end][start] = cost;
}

void Dijkstra(int start, int end, int N)
{
    int i, index, min = MAX;

    while(1)
    {
        index = MAX; min = MAX;
        for (i = 0; i < N; i++)
        {
            if(collected[i] == 0 && min > Mindist[i])
            {
                min = Mindist[i];
                index = i;
            }
        }
        if(index == MAX) break;
        collected[index] = 1;
        /* 找寻所有index的邻接点且未被收录的 */
        for (i = 0; i < N; i++)
        {
            if(citylist[i][index] == 1 && collected[i] == 0)
            {
                if(Mindist[i] > Mindist[index] + citytime[i][index])
                {
                    /* 除了更新最短路径外，还需要更新路费开销 */
                    /* 注意这里更新的部分只更新了一面，所以在输出的时候要注意哦 */
                    Mindist[i] = Mindist[index] + citytime[i][index];
                    citycost[i][start] = citycost[index][start] + citycost[i][index];
                }
                else if(Mindist[i] == Mindist[index] + citytime[i][index])
                {
                    /* 新路径的费用更低 */ 
                    if(citycost[i][start] > citycost[index][start] + citycost[i][index])
                    {
                        Mindist[i] = Mindist[index] + citytime[i][index];
                        citycost[i][start] = citycost[index][start] + citycost[i][index];
                    }
                }
            }
        }
    }
}