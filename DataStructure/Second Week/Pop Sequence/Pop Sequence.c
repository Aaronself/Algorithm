/*
解题思路：
熟悉堆栈的操作，包括创建堆栈，push和pop的操作都要掌握
本题考察的是堆栈的应用，解题的思路如下：
将接收到的数据存入一个数组，将它和我自己创建的一个堆栈输出的数据做比对
当我当前堆栈顶的数据和接收到的数据相等的时候，pop操作
不然就一直push操作，当遇到堆栈到顶或者堆栈空了也不能匹配输入的数组时，返回ERROR
否则就可以通过堆栈操作实现
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct stackRecord
{
    int capacity;
    int stackTop;
    int *array; 
}STACK;

int CanGetList(int Stack, int list[], int Num);
STACK* creat_stack(int StackNum);
void push(int pushnumber, STACK *s);
int pop(STACK *s);

int main()
{
    int M, N, K;
    int i, list[1000] = {0}, flag = 0;

    scanf("%d %d %d", &M, &N, &K);
    while(K)
    {
        for (i = 0; i < N; i++)
        {
            scanf("%d", &list[i]);
        }
        flag = CanGetList(M, list, N);

        if(flag)
            printf("YES");
        else
            printf("NO");

        if (K != 1)
            printf("\n");
        K--;
    }
}

int CanGetList(int Stack, int list[], int Num)
{
    STACK *stack_list;
    int i = 0, index, popnum;
    int j = 1;//尝试序列的内容
    int flag = 0;

    stack_list = creat_stack(Num);
    while(i<Num)
    {
        index = list[i];
        while(stack_list->stackTop == -1 || index != stack_list->array[stack_list->stackTop])
        {
            push(j, stack_list);
            j++;
            if(stack_list->stackTop > Stack - 1)//超出堆栈范围
            {
                return flag;                
            }

        }

        popnum = pop(stack_list);
        if(popnum == 0)
        {
            return flag;                
        }
        else if(popnum == index)
            i++;
    }

    flag = 1;
    return flag;
}

STACK* creat_stack(int StackNum)
{
    STACK *s;

    s = (STACK *)malloc(sizeof(struct stackRecord));
    s->stackTop = -1;
    s->capacity = StackNum;
    s->array = (int *)malloc(sizeof(int) * StackNum);

    return s;
}

void push(int pushnumber, STACK *s)
{
    s->stackTop++;
    s->array[s->stackTop] = pushnumber;
}

int pop(STACK *s)
{
    if(s->stackTop >= 0)
        return s->array[s->stackTop--];
    else
        return 0;
}