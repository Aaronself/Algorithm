#include <stdio.h>

void InsertSort(int list[]);
void Insert(int list[], int i);
int Compare(int list[]);
/* 控制选择哪种排序方式 */
int N, flag = 0;
int compare[100];

int main()
{
    int i;
    int input1[100], input2[100], tmp[100] = {0};
    int input_index = 0, com_index = 0;

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf(" %d", &input1[input_index]);
        input2[input_index] = input1[input_index];
        input_index++;
    }

    for (i = 0; i < N; i++)
        scanf(" %d", &compare[com_index++]);

    InsertSort(input1);
    if(!flag)
        HeapSort(input2, tmp, 0, N - 1);
}

void InsertSort(int list[])
{
    int i;
    int com_flag = 0;

    for (i = 1; i < N; i++)
    {
        Insert(list, i);
        if(!com_flag)
            com_flag = Compare(list);
        if(com_flag)
        {
            flag = 1;
            i++;
            Insert(list, i);
            printf("Insertion Sort\n");
            printf("%d", list[0]);
            for (i = 1; i < N; i++)
                printf(" %d", list[i]);

            return;
        }
    }
}

void Insert(int list[], int i)//实现从小到大排列
{
	int j, tmp;

	tmp = list[i];//待插入的数据
	for (j = i - 1; j >= 0 && list[j] > tmp; j--)
	{
		list[j + 1] = list[j];
	}
	list[j + 1] = tmp;
}

/* 返回0代表比较失败，返回1代表比较成功 */
int Compare(int list[])
{
    int i;

    for (i = 0; i < N; i++)
    {
        if(list[i] != compare[i])
            return 0;
    }
    return 1;
}