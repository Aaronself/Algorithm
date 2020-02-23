/*
希尔排序：
将数据量较大的数据逻辑上分为多组，每组之间的下标差称为增量
先将较少的数据按照插入排序的方法排序，然后控制增量gap/2，
每次在swap中不必将这一个逻辑分组排列完整，可按照循环的i++来慢慢完成
一个逻辑数组的排列
中间很巧妙的地方：
1.gap的设置，会影响后续的时间复杂度
2.两层循环的设置，巧用gap遍历整个逻辑分组
*/

#include <stdio.h>

void swap(int list[], int i, int gap);

int main()
{
	int n, list[10];
	int i, j, gap, tmp;

	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &list[i]);
	}

	for (gap = n/2; gap > 0; gap = gap / 2)
	{
		for (i = gap; i < n; i++)
		{
			swap(list, i, gap);
		}
	}

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
}

void swap(int list[], int i, int gap)
{
	int j, tmp;

	tmp = list[i];
	for (j = i - gap; j >= 0 && list[j] > tmp; j-=gap)
	{
		list[j + gap] = list[j];
	}
	list[j + gap] = tmp;
}