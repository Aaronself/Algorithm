/*
����˼·��
��������һ�����ƣ�����һ��������к͵����⣬���Ǹ��ݲ��Ե�Ĳ�ͬ������ϸ΢�ĵ���
����������£����������ȫС�ڵ���0�����������������һ����־λflag
flag = 0����ȫ��С��0��flag = 1���������ݵ���0�� flag = 2���������ݴ���0
�������Щ���������Ӧ����
������VS�У���������ʾwarning������������
*/

#include <stdio.h>

int main()
{
	int i, j, n, flag = 0;
	int list[10000];
	int left = 0, right = 0;
	long int max = 0, sum = 0;

	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
		scanf_s("%d", &list[i]);

	for (i = 0; i < n; i++)
	{
		sum = 0;
		if (flag == 0 || flag == 1)
		{
			if (list[i] > 0)//�ж������е���Ϊ���ڵ���0
				flag = 2;
			else if (list[i] == 0)
			{
				flag = 1;
				left = right = i;
			}	
			else if (list[i] < 0 && flag != 1)
				flag = 0;
		}
		for (j = i; j < n; j++)
		{
			if (sum + list[j] >= 0)
			{
				sum = sum + list[j];
				if (sum > max)
				{
					max = sum;
					left = i;
					right = j;
				}
				else if (sum == max)
				{
					if (left + right > i + j)
					{
						left = i;
						right = j;
					}
				}
			}
			else
				break;
		}
	}

	if (max > 0 || flag == 1)
	{
		printf("%ld %d %d\n", max, list[left], list[right]);
	}
	else if (flag == 0)
	{
		printf("0 %d %d", list[0], list[n - 1]);
	}
}