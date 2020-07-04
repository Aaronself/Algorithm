#include <stdio.h>
#include <math.h>
#define MAX 32768
#define Null -1
#define Maxsize 101

void BuildEdge(int N, int MaxJumpDis);
float Distance(int i, int j);
int DisToShore(int i);
void Floyd(int N);
void findmin(int entrance_index, int export_index);
void printpath(int i, int j);

int list[Maxsize][Maxsize];
int D[Maxsize][Maxsize];
int lastpath[Maxsize][Maxsize];
int Entrance[Maxsize] = {0}, Export[Maxsize] = {0};
int Node[Maxsize][2];
int save_flag = 0;
int main()
{
    int i, j, k;
    int N, MaxJumpDis;
    int entrance_index = 0, export_index = 0;

    scanf("%d %d", &N, &MaxJumpDis);
    if(MaxJumpDis >= 42.5)
    {
        printf("1\n");
        return 0;
    }
    if(N == 0)
    {
        printf("0\n");
        return 0;
    }
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &j, &k);
        Node[i][0] = j;
        Node[i][1] = k;
    }
    BuildEdge(N, MaxJumpDis);
    /* 找到鳄鱼入口 */
    for (i = 0; i < N; i++)
    {
        if(Distance(-1, i) <= MaxJumpDis + 7.5)
            Entrance[entrance_index++] = i;
    }
    Floyd(N);
    /* 找到鳄鱼出口 */
    for (i = 0; i < N; i++)
    {
        if(DisToShore(i) <= MaxJumpDis)
            Export[export_index++] = i;
    }
    findmin(entrance_index, export_index);
    
    return 0;
}

void BuildEdge(int N, int MaxJumpDis)
{
    int i, j;
    int length;

    for (i = 0; i < Maxsize; i++)
    {
        for (j = 0; j < Maxsize; j++)
        {
            list[i][j] = MAX;
        }
    }
    
    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            length = Distance(i, j);
            if(length <= MaxJumpDis)
            {
                list[i][j] = 1;
                list[j][i] = 1;
            }
        }
    }
}

float Distance(int i, int j)
{
    float num;
    if(i == Null)
    {
        num = sqrt(pow(Node[j][0], 2) + pow(Node[j][1], 2));
    }
    else if(j == Null)
    {
        num = sqrt(pow(Node[i][0], 2) + pow(Node[i][1], 2));
    }
    else
    {
        num = sqrt(pow((Node[i][0] - Node[j][0]), 2) + pow((Node[i][1] - Node[j][1]), 2));
    }
    return num;
}

int DisToShore(int i)
{
    int dis1, dis2;
    if(Node[i][0] > 0)
        dis1 = 50 - Node[i][0];
    else
        dis1 = Node[i][0] + 50;
    if (Node[i][1] > 0)
        dis2 = 50 - Node[i][1];
    else
        dis2 = Node[i][1] + 50;
    if(dis1>dis2)
        return dis2;
    else
        return dis1;
}

/* floyd算法找到所有鳄鱼之间的联通集 */
void Floyd(int N)
{
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            D[i][j] = list[i][j];
            lastpath[i][j] = MAX;
        }
    }

    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if(D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    lastpath[i][j] = k;
                }
            }
        }
    }
}

void findmin(int entrance_index, int export_index)
{
    int i, j, min_i = 0, min_j = 0;
    int min = MAX;

    for (i = 0; i < entrance_index; i++)
    {
        for (j = 0; j < export_index; j++)
        {
            if(D[Entrance[i]][Export[j]] < min)
            {
                if(Entrance[i] == Export[j])
                {
                    printf("2\n");
                    printf("%d %d\n", Node[min_i][0], Node[min_i][1]);
                    return;
                }
                min = D[Entrance[i]][Export[j]];
                min_i = Entrance[i];
                min_j = Export[j];
            }
            else if(D[Entrance[i]][Export[j]] == min && min != MAX)
            {
                if(Distance(-1, Entrance[i]) < Distance(-1, min_i))
                {
                    min = D[Entrance[i]][Export[j]];
                    min_i = Entrance[i];
                    min_j = Export[j];
                }
            }
        }
    }
    if(D[min_i][min_j] >= MAX)
    {
        printf("0\n");
        return;
    }
    else
    {
        printf("%d\n", D[min_i][min_j] + 2);
        /* 分而治之实现打印 */
        printf("%d %d\n", Node[min_i][0], Node[min_i][1]);
        printpath(min_i, min_j);
        if(min_i != min_j)
            printf("%d %d", Node[min_j][0], Node[min_j][1]);
    }
}

void printpath(int i, int j)
{
    int k;

    k = lastpath[i][j];
    if(k == MAX)
        return;
    printpath(i, k);
    printf("%d %d\n", Node[k][0], Node[k][1]);
    printpath(k, j);
}