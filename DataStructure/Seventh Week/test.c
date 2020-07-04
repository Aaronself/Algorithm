/*
解题思路：
主体算法为Floyd算法，这个为多源最短路径的算法
再找每一行中的最大值，这个就是当前动物最难变成其他动物所需要的咒语数
对所有的行最大值挑一个最小值，此为最优解
*/

#include <stdio.h>
#include <stdlib.h>
#define Maxsize 100
#define MAX 10000
#define Null -1

void init(int N);
void Floyd(int N);
int FindMaxPath(int N, int i);

int list[Maxsize][Maxsize];
int D[Maxsize][Maxsize];

int main()
{
    int i, j, k, l;
    int N, M;
    int maxdist, animal = 0, mindist = MAX;

    
    scanf("%d %d", &N, &M);
    /* 多源最短路径 */
    init(N);
    for (i = 0; i < M;i++)
    {
        scanf("%d %d %d", &j, &k, &l);
        j = j - 1; k = k - 1;
        /* 从i-j的咒语长度为l */
        list[j][k] = l;
        /* 从j-i的咒语长度为l，只不过顺序是倒过来的 */
        list[k][j] = l;
    }
    Floyd(N);
    for (i = 0; i < N; i++)
    {
        maxdist = FindMaxPath(N, i);
        if(maxdist == MAX)
        {
            printf("0\n");
            return 0;
        }
        if(maxdist < mindist)
        {
            mindist = maxdist;
            animal = i + 1;
        }
    }
    printf("%d %d\n", animal, mindist);
    return 0;
}

void init(int N)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            list[i][j] = MAX;
    }
}

void Floyd(int N)
{
    int i, j, k;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            D[i][j] = list[i][j];
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
                }
            }
        }
    }
}

int FindMaxPath(int N, int i)
{
    int j, max = 0;
    for (j = 0; j < N; j++)
    {
        if(i != j && D[i][j] > max)
        {
            max = D[i][j];
        } 
    }
    return max;
}
