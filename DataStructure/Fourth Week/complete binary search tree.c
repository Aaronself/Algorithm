/*
结论：对于一个（完全）搜索二叉树而言，它的中序遍历输出是从小到大的排列结果
*/
#include <stdio.h>
#include <stdlib.h>
#define Null -1

typedef struct TreeNode *Tree;
struct TreeNode{
    int num;
    Tree Left, Right;
};

int N, t = 0;
int list[1001], out[1000];

void Inorder(int node);
int cmpfunc(const void *a, const void *b);
int main()
{
    int i;

    scanf("%d", &N);
    for (i = 0; i < N; i++) 
        scanf("%d", &list[i]);
    qsort(list, N, sizeof(int), cmpfunc);/* 调用qsort的排序方法 */
    Inorder(0);
    for (i = 0; i < N; i++)
        printf("%d ", out[i]);
}
/* out中的node代表了在层序遍历中的坐标，当根节点为坐标0的时候 */
/* Inorder，对排列好的树做递归中序遍历，node记录了该节点的父节点的坐标。父节点的左儿子和右儿子的节点坐标可以被 */
/* 父节点的左儿子和右儿子的节点坐标可以被计算为root * 2 + 1/root * 2 + 2 */
/* 而list中又有排列好的数组，排列的顺序与中序遍历完全二叉搜索树的的结果相同 */
/* 所以只需赋值即可，node又提供了out的坐标，很简单不用建树即可完成 */
void Inorder(int node)
{
    if(node >= N) return;
    Inorder(node * 2 + 1);
    out[node] = list[t++];
    Inorder(node * 2 + 2);
}

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}