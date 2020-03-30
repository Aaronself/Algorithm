/*
对于这种集合的操作，包括并，删除，插入等等，由于给的输入是1-N的部分
所以可把它映射到数组的下标上，即数组的下标代表了机器号
数组中的数字大于0代表了父节点的下标，小于0代表了这颗树的规模
整体而言在优化上可以多加考虑，采用路径优化后可达a*logN的时间复杂度
*/
#include <stdio.h>
#include <stdlib.h>

void Link(int n1, int n2);
void Check(int n1, int n2);
int *list, *ptr;

int main()
{
    int i, N, n1, n2, num = 0;
    char a;

    scanf("%d", &N);
    list = (int *)malloc((N+1)*sizeof(int));
    if(!list) return 0;
    ptr = list;
    for (i = 0; i <= N; i++)
        *list++ = -1;
    list = ptr;
    a = getchar();
    while(a != 'S')/* 优化：采用switch优化，将其转化为三个分支 */
    {
        if(a == 'I')
        {
            scanf(" %d %d", &n1, &n2);       
            Link(n1, n2);
        }
        else if(a == 'C')
        {
            scanf(" %d %d", &n1, &n2);
            Check(n1, n2);
        }
        else if(a == 'S')
            break;
        else
            scanf(" %d %d", &n1, &n2);
        a = getchar();
    }
    for (i = 1; i <= N; i++)
    {
        printf("%d ", list[i]);
        if(list[i] <= -1)
            num++;
    }
    if(num >= 2)
        printf("There are %d components.", num);
    else
        printf("The network is connected.");
}
/* 优化：把找根节点单独作为一个函数，最后通过尾递归来通过find函数将路径压缩 */
void Link(int n1, int n2)
{
    int root1, root2;

    if(list[n1] <= -1 && list[n2] <= -1)
    {
        list[n1] = n2;
        list[n2]--;
        return;
    }
    else
    {
        if(list[n1] <= -1)
            root1 = n1;
        else
            for (root1 = list[n1]; list[root1] > 0; root1 = list[root1]);
        if(list[n2] <= -1)
            root2 = n2;
        else
            for (root2 = list[n2]; list[root2] > 0; root2 = list[root2]);
        if(root1 != root2) 
        {
            if(list[root1] < list[root2]) 
            {
                list[root2] = root1;
                list[root1]--;
            }
            else if(list[root1] > list[root2]) 
            {
                list[root1] = root2;
                list[root2]--;
            }
            else if(list[root1] == list[root2])
            {
                list[root1] = root2;
                list[root2]--;
            }
        }
    }
}

void Check(int n1, int n2)
{
    int root1, root2;

    if(list[n1] <= -1 && list[n2] <= -1)
    {
        printf("no\n");
        return;
    }
    else if(list[n1] <= -1)
    {
        for (root2 = list[n2]; list[root2] > 0; root2 = list[root2]);
        if(root2 == n1){ printf("yes\n"); return;}
        else {printf("no\n");return;}
    }
    else if(list[n2] <= -1)
    {
        for (root1 = list[n1]; list[root1] > 0; root1 = list[root1]);
        if(root1 == n2){ printf("yes\n"); return;}
        else {printf("no\n");return;}
    }
    else
    {
        for (root1 = list[n1]; list[root1] > 0; root1 = list[root1]);
        for (root2 = list[n2]; list[root2] > 0; root2 = list[root2]);
        if(root1 != root2) printf("no\n");
        else printf("yes\n");
    }
}
