/*
六度空间：
解题思路：BFS的变种，只不过需要控制一下degree的层数
记录这一层应该要输出的最后一个i，当目前的输出跟i相同时，即这一层结束
BFS，利用队列完成搜索工作
*/

#include <stdio.h>
#include <stdlib.h>
#define Null -1
#define Maxsize 1001

void clearvisit();
int sixdegree(int num, int N);
void BuildQuene();
int isEmpty();
void EnQuene(int num);
int OutQuene();
struct QueneNode{
    int list[Maxsize];
    int rear;
    int front;
} Quene;
int list[Maxsize][Maxsize];
int visitlist[Maxsize] = {0};

int main()
{
    int i, N, E;
    int j, k, num;
    float percentage;

    scanf("%d %d", &N, &E);
    for (i = 0; i < N;i++)
    {
        for (j = 0; j < N; j++)
            list[i][j] = 0;
    }
    for (i = 0; i < E; i++)
    {
        scanf(" %d %d", &j, &k);
        list[j][k] = 1;
        list[k][j] = 1;
    }
    clearvisit();
    for (i = 1; i <= N; i++)
    {
        num = sixdegree(i, N);
        percentage = (float)num / N * 100;
        printf("%d: %.2f%%", i, percentage);
        clearvisit();
        if(i !=  N)
            printf("\n");
    }
}

void clearvisit()
{
    int i;
    for (i = 0; i < Maxsize; i++)
        visitlist[i] = 0;
}

int sixdegree(int num, int N)
{
    int i, out, tmp = 0, end;
    int degree = 1,sum = 1;

    BuildQuene();
    EnQuene(num);
    visitlist[num] = 1;
    while(degree <= 6 && !isEmpty())
    {
        out = OutQuene();
        for (i = 0; i <= N; i++)
        {
            if(list[out][i] == 1 && visitlist[i] != 1)
            {
                visitlist[i] = 1;
                //printf("i: %d ", i);
                sum++;
                EnQuene(i);
                end = i;
            }
        }
        //printf("out: %d, tmp: %d ", out, tmp);
        if(degree == 1)
        {
            tmp = end;
            degree++;
        }
        else if(out == tmp)
        {
            tmp = end;
            degree++;
        }
    }

    return sum;
}

void BuildQuene()
{
    int i;

    for (i = 0; i < Maxsize; i++)
        Quene.list[i] = 0;
    Quene.front = 0;
    Quene.rear = 0;
}

int isEmpty()
{
    if(Quene.front == Quene.rear)
        return 1;
    else
        return 0;
}

void EnQuene(int num)
{
    Quene.rear = (Quene.rear + 1) % Maxsize;
    Quene.list[Quene.rear] = num;
}

int OutQuene()
{
    if(isEmpty())
        return Null;
    else
    {
        Quene.front = (Quene.front + 1) % Maxsize;
        return Quene.list[Quene.front];
    }
}