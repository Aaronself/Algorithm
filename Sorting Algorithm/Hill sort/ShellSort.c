/*
ϣ������
���������ϴ�������߼��Ϸ�Ϊ���飬ÿ��֮����±���Ϊ����
�Ƚ����ٵ����ݰ��ղ�������ķ�������Ȼ���������gap/2��
ÿ����swap�в��ؽ���һ���߼����������������ɰ���ѭ����i++���������
һ���߼����������
�м������ĵط���
1.gap�����ã���Ӱ�������ʱ�临�Ӷ�
2.����ѭ�������ã�����gap���������߼�����
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