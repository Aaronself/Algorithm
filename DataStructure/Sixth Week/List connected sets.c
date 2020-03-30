/*
图论的两种标准遍历方式：DFS和BFS
DFS作为深度优先搜索，利用递归地方式完成
BFS作为广度优先搜索，利用堆栈完成搜索功能
区分两种遍历方式的优势和劣势
*/
#include <stdio.h>
#include <stdlib.h>
#define Null -1

struct QueneNode{
    int list[10];
    int front;
    int rear;
} Quene;

void DFS(int num);
void BFS(int num);
void BuildQuene();
int isEmpty();
void EnQuene(int num);
int OutQuene();
int list[10][10];
int visitlist[10];
int main()
{
    /* N为图中顶点数，E为边数 */
    int i, N, E;
    int j, k;

    scanf("%d %d", &N ,&E);
    for (i = 0; i < 10;i++)
    {
        for (j = 0; j < 10; j++)
        {
            list[i][j] = 0;
        }
    }
    for (i = 0; i < E; i++)
    {
        /* 将图存储至数组中 */
        scanf("%d %d", &j, &k);
        list[j][k] = 1;
        list[k][j] = 1;
    }

    /* DFS BFS */
    for (i = 0; i < N; i++)
        visitlist[i] = 0;
    for (i = 0; i < N; i++)   
        if(visitlist[i] != 1)
        {
            printf("{ ");
            DFS(i);
            printf("}\n");
        }
    for (i = 0; i < 10; i++)
        visitlist[i] = 0;
    for (i = 0; i < N; i++)   
        if(visitlist[i] != 1)
        {
            printf("{ ");
            BFS(i);
            printf("}\n");
        }

    return 0;
}

void DFS(int num)
{
    int i;

    visitlist[num] = 1;
    printf("%d ", num);
    /*依次访问num的邻接节点*/
    for (i = 0; i < 10; i++)
    {
        if(list[num][i] && visitlist[i] != 1)
            DFS(i);
    }
}

void BFS(int num)
{
    int i, outnum;

    BuildQuene();
    EnQuene(num);
    visitlist[num] = 1;
    printf("%d ", num);
    while(!isEmpty())
    {
        outnum = OutQuene();
        for (i = 0; i < 10;i++)
        {
            if(list[outnum][i] && visitlist[i] != 1)
            {
                visitlist[i] = 1;
                printf("%d ", i);
                EnQuene(i);
            }      
        }
    }
}

void BuildQuene()
{
    int i;
    for (i = 0; i < 10;i++)
        Quene.list[i] = Null;
    Quene.front = 0;
    Quene.rear = 0;
}

int isEmpty()
{
    if(Quene.front == Quene.rear)
    {
        return 1;
    }
    else
        return 0;
}

void EnQuene(int num)
{
    Quene.rear = (Quene.rear+1) % 10;
    Quene.list[Quene.rear] = num;
}

int OutQuene()
{
    if(!isEmpty())
    {
        Quene.front = (Quene.front+1) % 10;
        return Quene.list[Quene.front];
    }
    else
        return Null;
}

