/*
冒泡排序：
两层循环遍历数组，每一次大循环的遍历相当于循环了整个数组的无序部分
代码的思路即每一次大循环的遍历找出当前无序部分的最大值或者最小值，
只要遇到一个比当前比较对象小的，即交换两者位置，等遍历完数据，
即可得到当前无序部分的最小值，然后外层的大循环遍历整个数组，完成数据排序
*/

#include <stdio.h>

int main()
{
	int n, list[10];
	int i, j, tmp;

	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &list[i]);
	}

	for (i = 0; i < n; i++)//实现从小到大排序
	{
		for (j = i + 1; j < n; j++)
		{
			if (list[i] > list[j])
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
}