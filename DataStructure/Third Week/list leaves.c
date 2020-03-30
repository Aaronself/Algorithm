/*
解题思路：
读取参数，跟上一题不一样的地方在于，缺少了自己本身的参数，于是在建结构体的时候给补上即可
为了实现层序遍历树结构，这里建立了一个队列，先把树的根节点入队，然后pop出来的时候，把根节点的左右子树入队
然后pop的时候，把根节点的左子树的左右子树print出来，再print右子树的左右子树，然后再将其入队
最后循环即可实现层序遍历树的结构
找一个控制输出格式的变量即可
*/

#include <malloc.h>
#include <stdio.h>

#define Null -1
#define MaxSize 10

struct ReadInput
{
    int num;
    int left;
    int right;
} input[MaxSize];

struct quenu
{
    int list[4];
    int front; //队列头
    int rear;  //队列尾
} QuenuList;

int BuildTree();
void ChangeOrder(int top);
void CreatQuenu();
int AddToQuenu(int num);
int OutOfQuenu();

//定义一个打印的数字，来控制后面的打印格式
int PrintNum = 0;

int main()
{
    int top_num;

    top_num = BuildTree();
    CreatQuenu();
    ChangeOrder(top_num);

    return 0;
}

int BuildTree()
{
    int i, N, check[MaxSize] = {0};
    int index;
    char left, right;

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf(" %c %c", &left, &right);
        input[i].num = i;
        if (left == '-')
            input[i].left = Null;
        else
        {
            input[i].left = left - '0';
            check[left - '0'] = 1;
        }

        if (right == '-')
            input[i].right = Null;
        else
        {
            input[i].right = right - '0';
            check[right - '0'] = 1;
        }

        if (left == '-' && right == '-')
            PrintNum++;
    }

    for (index = 0; index < N; index++)
    {
        if (!check[index])
            break;
    }

    return index;
}

void ChangeOrder(int top)
{
    int OrderList[MaxSize] = {0};
    int out[4], out_index, j, num;
    int i, left_node, right_node;
    int flag = 0;

    //printf("%d ", OrderList[0]);
    OrderList[0] = input[top].num; //index == num
    AddToQuenu(OrderList[0]);
    i = 1;
    while (1) //修改入口条件
    {
        out_index = 0;
        while (QuenuList.front != QuenuList.rear)
        {
            out[out_index] = OutOfQuenu();
            out_index++; //A
        }
        j = 0;
        while (j < out_index)
        {
            num = out[j];
            left_node = input[num].left;
            right_node = input[num].right;
            //printf("%d %d %d\n", num, left_node, right_node);
            if (left_node != Null)
            {
                //printf("l:%d ", left_node);
                OrderList[i] = left_node;
                AddToQuenu(OrderList[i]);
                i++;
            }
            if (right_node != Null)
            {
                //printf("r:%d ", right_node);
                OrderList[i] = right_node;
                AddToQuenu(OrderList[i]);
                i++;
            }

            if (left_node == Null && right_node == Null)
            {
                if (PrintNum != 1)
                {
                    printf("%d ", num);
                    PrintNum--;
                }
                else
                {
                    printf("%d", num);
                    flag = 1;
                }
            }

            j++;
        }
        if (flag == 1)
            break;
    }
}

void CreatQuenu()
{
    int i;

    for (i = 0; i < 4; i++)
        QuenuList.list[i] = Null;

    QuenuList.front = QuenuList.rear = 0;
}

int AddToQuenu(int num)
{
    if ((QuenuList.front + 1) % 4 == QuenuList.rear)
        return Null;
    else
    {
        QuenuList.front = (QuenuList.front + 1) % 4;
        QuenuList.list[QuenuList.front] = num;
        return 1;
    }
}

int OutOfQuenu()
{
    int num;

    if (QuenuList.front == QuenuList.rear)
        return Null;
    else
    {
        QuenuList.rear = (QuenuList.rear + 1) % 4;
        num = QuenuList.list[QuenuList.rear];
        return num;
    }
}