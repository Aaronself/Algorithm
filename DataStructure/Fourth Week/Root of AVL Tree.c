/*
解题思路：
1.首先要构造树，包括计算树的avl值
2.构造四种旋转模板，其中LR和RL是可以分解为先右旋再左旋和先左旋再右旋（后续展开）
3.关键点在于何时判断是否旋转。
本来思路：再插入完成后遍历整棵树，计算数的avl，再调整
进阶版：再插入的过程中完成调整，因为在插入过程中，已经完成了需要部分的遍历操作
插入完成后，直接计算avl，然后调整，最优策略
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 20
#define Null -1

typedef struct TreeNode *Tree;
struct TreeNode
{
    int num;
    Tree Left;
    Tree Right;
};

Tree NewTree(int num);
Tree InsertTree(Tree T, int num);
Tree RRSpin(Tree T);
Tree RLSpin(Tree T);
Tree LLSpin(Tree T);
Tree LRSpin(Tree T);
int TreeHeight(Tree T);
int Max(int a, int b);

int main()
{
    int i, N, list[MAXNUM];
    Tree T;

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &list[i]);
    }
    T = NewTree(list[0]);
    for (i = 1; i < N; i++)
    {
        T = InsertTree(T, list[i]);
    }

    printf("%d", T->num);

    return 0;
}

Tree NewTree(int num)
{
    Tree T;

    T = (Tree)malloc(sizeof(struct TreeNode));
    T->num = num;
    T->Left = T->Right = NULL;

    return T;
}

Tree InsertTree(Tree T, int num)
{
    if(!T)
        T = NewTree(num);
    else
    {
        if(num < T->num)
        {
            T->Left = InsertTree(T->Left, num);
            if(TreeHeight(T->Left) - TreeHeight(T->Right) == 2)
                T = (num < T->Left->num) ? LLSpin(T) : LRSpin(T);
        }    
        else if(num > T->num)
        {
            T->Right = InsertTree(T->Right, num);
            if(TreeHeight(T->Left) - TreeHeight(T->Right) == -2)
                T = (num > T->Right->num) ? RRSpin(T) : RLSpin(T);
        }
    }

    return T;
}

//除了旋转还需要调整avl值
Tree RRSpin(Tree T)
{
    Tree tmp1, tmp2;

    tmp1 = T;
    tmp2 = T->Right;
    tmp1->Right = tmp2->Left;
    tmp2->Left = tmp1;

    return tmp2;
}

Tree RLSpin(Tree T)
{
    Tree tmp1, tmp2, tmp3;

    tmp1 = T;
    tmp2 = T->Right;
    tmp3 = T->Right->Left;
    tmp1->Right = tmp3->Left;
    tmp2->Left = tmp3->Right;
    tmp3->Left = tmp1;
    tmp3->Right = tmp2;
    
    return tmp3;
}

Tree LLSpin(Tree T)
{
    Tree tmp1, tmp2;

    tmp1 = T;
    tmp2 = T->Left;
    tmp1->Left = tmp2->Right;
    tmp2->Right = tmp1;

    return tmp2;
}

Tree LRSpin(Tree T)
{
    Tree tmp1, tmp2, tmp3;

    tmp1 = T;
    tmp2 = T->Left;
    tmp3 = T->Left->Right;
    tmp1->Left = tmp3->Right;
    tmp2->Right = tmp3->Left;
    tmp3->Left = tmp2;
    tmp3->Right = tmp1;

    return tmp3;
}

int TreeHeight(Tree T)
{
    if (!T)
        return Null;
    else
        return Max(TreeHeight(T->Left), TreeHeight(T->Right)) + 1;
}

int Max(int a, int b)
{
    return (a >= b) ? a : b;
}