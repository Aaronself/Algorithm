/*
解题思路：
本题需要求解的是最大子列和，最暴力的做法即计算所有的子列和，找到其中最大的部分
但是通过分析子列和可以发现，当在计算某一个循环开始的子列和的时候，
如果当前的sum已经小于0了，其实是可以跳过这个循环。
原因如下：当前计算的sum小于0，即便加上后面的和大于0，
如果把整个子列和计算出来，还是不如直接计算后面的子列和。
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