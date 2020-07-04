/*
解题思路：
使用prim的算法，即构建一个cost的数组，代表了未收录的城镇到已收录城镇的最小开销
若该城镇已被收录，则cost中的值改为0即可
这样寻找到的与该树有连接的边的最小值，必定不构成回路
循环的退出条件即：找不到这样的顶点了
*/
#include <stdio.h>
#define Maxsize 1001
#define Null -1
#define MAX 32768

int Prim(int N);
int Findmincost(int cost[], int N);

int CityCost[Maxsize][Maxsize];

int main()
{
    int i, j, k, l;
    int N, M, cost;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            CityCost[i][j] = MAX;
    }
    /* 注意城镇是从1-N编号，数组下标从0-N-1 */
    for (i = 1; i <= M; i++)
    {
        /* cityA cityB cost */
        scanf("%d %d %d", &j, &k, &l);
        CityCost[j][k] = l;
        CityCost[k][j] = l;
    }

    cost = Prim(N);
    printf("%d", cost);

    return 0;
}   

/* 从城镇1开始 */
int Prim(int N)
{
    int i, index, costsum = 0, count = 1;
    /* Cost指未收录的城镇到已收录城镇的最小开销 */
    int Cost[Maxsize], parent[Maxsize];

    for (i = 1; i <= N; i++)
    {
        Cost[i] = CityCost[1][i];
        parent[i] = 1;/* 设置所有顶点的父节点为顶点1 */
    }
    Cost[1] = 0; parent[1] = -1;

    while(1)
    {
        /* 这样收录进来后一定不构成回路 */
        index = Findmincost(Cost, N);
        if(index == Null) 
            break;

        costsum += Cost[index];
        Cost[index] = 0;
        count++;

        /* 更新cost的花费 */
        for (i = 1; i <= N; i++)
        {
            if(Cost[i] != 0 && CityCost[index][i] < MAX)
            {
                if(Cost[i] > CityCost[index][i])
                {
                    Cost[i] = CityCost[index][i];
                    parent[i] = index;
                }
            }
        }
    }
    if(count < N) 
        costsum = -1;
    
    return costsum;
}

int Findmincost(int cost[], int N)
{
    int i;
    int min = MAX, index;

    for (i = 1; i <= N; i++)
    {
        if(cost[i] != 0 && cost[i] < min)
        {
            min = cost[i];
            index = i;
        }
    }
    if (min < MAX)
        return index;
    else
        return Null;
}