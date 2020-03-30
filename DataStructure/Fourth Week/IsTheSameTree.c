#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode* Tree;
struct TreeNode{
    int num;
    Tree Left, Right;
    int flag;
};

int CompareTree(Tree T, int N, int ComList[]);
int Check(Tree T, int num);
void ClearFlag(Tree T);
Tree BuildTree(int N, int list[]);
Tree NewTree(int num);
Tree InsertTree(Tree T, int num);
void FreeTree(Tree T);

int main()
{
    int i, N, L, res;
    int List[10], ComList[10];
    Tree T;

    scanf("%d", &N);
    while(N != 0)
    {  
        scanf(" %d", &L);
        for (i = 0; i < N; i++)
        {
            scanf("%d", &List[i]);//初始序列
        }
        T = BuildTree(N, List);
        while (L)
        {
            for (i = 0; i < N; i++)
            {
                scanf("%d", &ComList[i]);
            }
            res = CompareTree(T, N, ComList);
            ClearFlag(T);
            if(res)
                printf("Yes\n");
            else
                printf("No\n");

            L--;
        }
        FreeTree(T);
        scanf("%d", &N);
    }

    return 0;
}

int CompareTree(Tree T, int N, int ComList[])
{
    int i, res;

    if(ComList[0] == T->num)
        T->flag = 1;
    else
        return 0;
    
    for (i = 1; i < N; i++)
    {
        res = Check(T, ComList[i]);
        if(res == 0)
            return 0;
    }

    return 1;
}

int Check(Tree T, int num)//使用flag来判别是否已经经过该节点
{
    if(T->flag)//代表已经经过该节点
    {
        if(num > T->num)
            return Check(T->Right, num);
        else if (num < T->num)
            return Check(T->Left, num);
        else
            return 0;
    }
    else
    {
        if(num == T->num)
        {
            T->flag = 1;
            return 1;
        }
        else
            return 0;
    }
}

void ClearFlag(Tree T)
{
    if(T->Left)
        ClearFlag(T->Left);
    if(T->Right)
        ClearFlag(T->Right);
    T->flag = 0;
}

Tree BuildTree(int N, int list[])
{
    int i;
    Tree T;

    T = NewTree(list[0]);
    for (i = 1; i < N; i++)
    {
        T = InsertTree(T, list[i]);
    }

    return T;
}

Tree NewTree(int num)
{
    Tree T;

    T = (Tree)malloc(sizeof(struct TreeNode));
    T->num = num;
    T->Left = T->Right = NULL;
    T->flag = 0;

    return T;
}

Tree InsertTree(Tree T, int num)
{
    if(!T)
        T = NewTree(num);
    else
    {
        if(num > T->num)
            T->Right = InsertTree(T->Right, num);
        else
            T->Left = InsertTree(T->Left, num);
    }

    return T;
}

void FreeTree(Tree T)
{
    if(T->Left)
        FreeTree(T->Left);
    if(T->Right)
        FreeTree(T->Right);
    free(T);
}