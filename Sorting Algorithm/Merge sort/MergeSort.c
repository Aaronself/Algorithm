/*
�鲢����
�鲢���������˵ݹ��˼�룬�������黮��Ϊ��������С���飬
��ͨ���ݹ飬��С�����������Ϊ�����������飬����ʽ�����ڶ������Ľṹ
��ָ��˼�룬�ο�ϣ������
��ͬ�㣺����ͨ����С�Ĳ��ԣ���ͬ�㣺ϣ�����򻮷ֲ��õ��������У�
������õķָ�Ϊ�������顣
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
		//����ߵ�
		MergeSort(list, TmpList, left, center);
		//���ұߵ�
		MergeSort(list, TmpList, center + 1, right);
		//��
		Merge(list, TmpList, left, center, right);
	}
}

void Merge(int list[], int TmpList[], int left, int center, int right)//��С��������
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