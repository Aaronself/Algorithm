/*
解题思路：
此题于上一题类似，都是一个最大子列和的问题，但是根据测试点的不同，做了细微的调整
具体调整如下：首先是针对全小于等于0的情况，这里设置了一个标志位flag
flag = 0代表全体小于0，flag = 1代表有数据等于0， flag = 2代表有数据大于0
则根据这些情况做出相应调整
但是在VS中，代码有提示warning，具体后续解决
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
			if (list[i] > 0)//判断数组中的数为大于等于0
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