/*
拯救詹姆斯邦德
解题思路：这是一个改造的DFS
DFS利用递归的方式，类似于树结构的先序遍历
稍微注意一下控制距离的问题即可，注意边界问题
*/
#include <stdio.h>
#include <math.h>
#define Null -1
#define Maxsize 101

void clearvisit();
void BuildEdge(int N, int Maxdistance);
float Distance(int i, int j);
void DFS(int n, int N, int Maxdistance);
int DisToShore(int i);

int list[Maxsize][Maxsize];
int visited[Maxsize];
int Node[Maxsize][2];
int save_flag = 0;
int main()
{
    int i, j, k;
    int N, M, flag = 0;

    scanf("%d %d", &N, &M);
    if(N == 0)
    {
        printf("No");
        return;
    }
    for (i = 0; i < N; i++)
    {
        scanf(" %d %d", &j, &k);
        Node[i][0] = j;
        Node[i][1] = k;
    }
    for (i = 0; i < Maxsize; i++)
    {
        for (j = 0; j < Maxsize; j++)
        {
            list[i][j] = 0;
        }
    }
    BuildEdge(N, M);
    for (i = 0; i < N; i++)
    {
        clearvisit();
        if (Distance(-1, i) <= M + 7.5)
        {
            if(DisToShore(i) <= M)
                save_flag = 1;
            else
                DFS(i, N, M);
            if(save_flag)
                break;
        }
    }
    if(save_flag)
        printf("Yes");
    else
        printf("No");

    return 0;
}

void clearvisit()
{
    int i;
    for (i = 0; i < Maxsize; i++)
        visited[i] = 0;
}

void BuildEdge(int N, int Maxdistance)
{
    int i, j;
    int length;

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            length = Distance(i, j);
            if(length <= Maxdistance)
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

void DFS(int n, int N, int Maxdistance)
{
    int i;

    visited[n] = 1;

    for (i = 0; i < N; i++)
    {
        if(list[n][i] == 1 && visited[i] != 1)
        {
            //visited[i] = 1;
            //printf("i: %d inode: (%d ,%d), dis: %d  \n", i, Node[i][0],Node[i][1],DisToShore(i));
            if(DisToShore(i) <= Maxdistance)
            {
                save_flag = 1;
                return;
            }
            else
                DFS(i, N, Maxdistance);
        }
    }
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