/*
归并排序：
归并排序利用了递归的思想，将大数组划分为左右两个小数组，
再通过递归，将小数组继续划分为左右两个数组，其形式类似于二叉树的结构
其分割的思想，参考希尔排序。
相同点：都是通过大化小的策略；不同点：希尔排序划分采用的增量序列，
这个采用的分割为左右数组。
*/
#include <stdio.h>

void MergeSort(int list[], int TmpList[], int left, int right);
void Merge(int list[], int TmpList[], int left, int center, int right);

int main()
{
	int i, n, list[10], TmpList[10];
	int left_end, right_end;

	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
		scanf_s("%d", &list[i]);

	left_end = 0;
	right_end = n - 1;
	MergeSort(list, TmpList, left_end, right_end);

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
}

void MergeSort(int list[], int TmpList[], int left, int right)
{
	int center;

	if (left < right)
	{
		center = (left + right) / 2;
		//分左边的
		MergeSort(list, TmpList, left, center);
		//分右边的
		MergeSort(list, TmpList, center + 1, right);
		//归
		Merge(list, TmpList, left, center, right);
	}
}

void Merge(int list[], int TmpList[], int left, int center, int right)//从小到大排序
{
	int i, j, k;
	i = left;
	j = center + 1;
	k = 0;

	while (i <= center && j <= right)
	{
		if (list[i] <= list[j])
		{
			TmpList[k] = list[i];
			k++; i++;
		}
		else if (list[j] < list[i])
		{
			TmpList[k] = list[j];
			k++; j++;
		}
	}
	
	if (i == center + 1)
	{
		while (j <= right)
		{
			TmpList[k] = list[j];
			k++; j++;
		}
	}
	else if (j == right + 1)
	{
		while (i <= center)
		{
			TmpList[k] = list[i];
			k++; i++;
		}
	}

	for (i = left; i <= right; i++)
		list[i] = TmpList[i - left];
}