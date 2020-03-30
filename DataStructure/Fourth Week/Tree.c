/*
该程序需要深刻的理解递归的操作，这样才可将树的根节点完整的返回
搜索树的操作如下：
插入（新建/插入）找到合适位置插入数据
删除 困难点在于理解递归操作，即返回根节点
寻找 最大点位于右子树的右节点 最小点位于左子树的左节点
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }

    return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert( BinTree BST, ElementType X )
{
    BinTree T;

    if(!BST)
    {
        T = (BinTree)malloc(sizeof(struct TNode));
        T->Data = X;
        T->Left = T->Right = NULL;

        return T;
    }
    else
    {
        if(X > BST->Data)
            BST->Right = Insert(BST->Right, X);
        else if(X < BST->Data)
            BST->Left = Insert(BST->Left, X);
    }

    return BST;
}

BinTree Delete( BinTree BST, ElementType X )
{
    BinTree tmp;

    if(!BST)
    {
        printf("Not Found\n");
        return BST;
    }
    else if(X > BST->Data)
        BST->Right = Delete(BST->Right, X);
    else if(X < BST->Data)
        BST->Left = Delete(BST->Left, X);
    else if(X == BST->Data)
    {
        if(BST->Left == NULL && BST->Right == NULL)
        {
            tmp = BST;
            BST = NULL;
            free(tmp);
        }else if(BST->Left == NULL)
        {
            tmp = BST;
            BST = BST->Right;
            free(tmp);
        }
        else if(BST->Right == NULL)
        {
            tmp = BST;
            BST = BST->Left;
            free(tmp);
        }
        else if(BST->Left && BST->Right)
        {
            tmp = FindMax(BST->Left);
            BST->Data = tmp->Data;
            BST->Left = Delete(BST->Left, BST->Data);
        }
    }
    
    return BST;
}

Position Find( BinTree BST, ElementType X )
{
    if(!BST)
        return NULL;
    if(X > BST->Data)
        BST = Find(BST->Right, X);
    else if(X < BST->Data)
        BST = Find(BST->Left, X);
    else if(X == BST->Data)
    {
        return BST;
    }

    return BST;
}

Position FindMin( BinTree BST )
{
    if(!BST)
        return NULL;
    while (BST->Left)
    {
        BST = BST->Left;
    }

    return BST;
}
Position FindMax( BinTree BST )
{
    if(!BST)
        return NULL;
    if(!BST)
        return NULL;
    else if(!BST->Right)
        return BST;
    else if(BST->Right)
        BST = FindMax(BST->Right);
}