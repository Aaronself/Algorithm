/*
插入排序：
将待排序的数组视为两个部分，前半部分为有序数组，后半部分为无序数组
将无序数组中的每个数都插入到前方的有序数组部分，需要进行n-1次
插入的过程分为两个部分，将有序数组依次后移，并与待插入数据比较
将待插入数据插入合适的位置
*/

#include <stdio.h>

void insert(int list[], int i);

int main()
{
	int n, list[10];
	int i, j, index;

	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &list[i]);
	}

	for (i = 1; i < n; i++)//视第一个数据为有序数组，后面的为无序数组
	{
		insert(list, i);
	}

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
}

void insert(int list[], int i)//实现从小到大排列
{
	int j, tmp;

	tmp = list[i];//待插入的数据
	for (j = i - 1; j >= 0 && list[j] > tmp; j--)
	{
		list[j + 1] = list[j];
	}
	list[j + 1] = tmp;
}