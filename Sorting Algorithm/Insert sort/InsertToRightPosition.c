/*
��������
���������������Ϊ�������֣�ǰ�벿��Ϊ�������飬��벿��Ϊ��������
�����������е�ÿ���������뵽ǰ�����������鲿�֣���Ҫ����n-1��
����Ĺ��̷�Ϊ�������֣��������������κ��ƣ�������������ݱȽ�
�����������ݲ�����ʵ�λ��
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

	for (i = 1; i < n; i++)//�ӵ�һ������Ϊ�������飬�����Ϊ��������
	{
		insert(list, i);
	}

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
}

void insert(int list[], int i)//ʵ�ִ�С��������
{
	int j, tmp;

	tmp = list[i];//�����������
	for (j = i - 1; j >= 0 && list[j] > tmp; j--)
	{
		list[j + 1] = list[j];
	}
	list[j + 1] = tmp;
}