/*
����˼·��
������Ҫ������������кͣ�������������������е����кͣ��ҵ��������Ĳ���
����ͨ���������кͿ��Է��֣����ڼ���ĳһ��ѭ����ʼ�����к͵�ʱ��
�����ǰ��sum�Ѿ�С��0�ˣ���ʵ�ǿ����������ѭ����
ԭ�����£���ǰ�����sumС��0��������Ϻ���ĺʹ���0��
������������кͼ�����������ǲ���ֱ�Ӽ����������к͡�
*/

#include <stdio.h>

int main()
{
	long int i, j, n;
	int list[100000];
	long int max = 0, sum = 0;

	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
		scanf_s("%d", &list[i]);

	for (i = 0; i < n; i++)
	{
		sum = list[i];
		for (j = i + 1; j < n; j++)
		{
			if (sum + list[j] > 0)
			{
				sum = sum + list[j];
				if (sum > max)
					max = sum;
			}
			else
				break;
		}
	}

	if (max > 0)
		printf("%d", max);
	else
		printf("0");
}