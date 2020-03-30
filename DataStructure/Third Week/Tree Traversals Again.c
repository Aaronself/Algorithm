/*
解题：
给了一个树的中序遍历的结果，通过一个堆栈的形式，要求这棵树的后序遍历的结果
对比中序遍历和后序遍历，他们的push进栈的顺序是一致的，只不过何时pop不同
*/

#include <malloc.h>
#include <stdio.h>

#define Null -1

struct Stack
{
    int list[31];
    int depth;
    int top;
} TreeStack;

int GetInput(int N, int list[]);
int PostOrder(int left, int right, int root, int InOrder[]);
void BuildStack(int depth);
int Push(int number);
int Pop();

int PreOrder[31];
int printnum = 0;
int printmax = 0;

int main()
{
    int i, N;
    int InOrder[31];

    scanf("%d\n", &N);
    printmax = N;
    GetInput(N, InOrder);
    PostOrder(0, N - 1, 0, InOrder);
}

int GetInput(int N, int list[]) //返回根节点
{
    int i, j, index_pre, index_in;
    char a[5];

    i = 0;
    index_pre = 0;
    index_in = 0;
    BuildStack(N);
    while (i < N)
    {
        scanf("%s", &a);
        if (a[1] == 'u')
        {
            scanf("%d", &j);
            PreOrder[index_pre] = j;
            index_pre++;
            Push(j);
        }
        else if (a[1] == 'o')
        {
            list[index_in] = Pop();
            index_in++;
            i++;
        }
    }

    return 0;
}

int PostOrder(int left, int right, int root, int InOrder[])
{
    int i;
    if(left > right)
        return 0;
    for (i = left; i < right; i++)
    {
        if(InOrder[i] == PreOrder[root])
            break;
    }

    PostOrder(left, i - 1, root + 1, InOrder);
    PostOrder(i+1, right, root + 1 + i - left, InOrder);
    printf("%d", PreOrder[root]);
    printnum++;
    if(printnum <= printmax - 1)
        printf(" ");

    return 0;
}

void BuildStack(int depth)
{
    int i;

    for (i = 0; i < 30; i++)
    {
        TreeStack.list[i] = 0;
    }
    TreeStack.depth = depth;
    TreeStack.top = -1;
}

int Push(int number)
{
    if (TreeStack.top == TreeStack.depth - 1)
        return Null;
    else
    {
        TreeStack.top++;
        TreeStack.list[TreeStack.top] = number;
    }

    return 0;
}

int Pop()
{
    int i;

    if (TreeStack.top == -1)
        return Null;
    else
    {
        i = TreeStack.list[TreeStack.top];
        TreeStack.top--;
        return i;
    }
}