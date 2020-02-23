#include <stdio.h>

void swap(int list[], int i, int index);

int main()
{
	int n;
	int i, j, a, index, tmp;
	int list[1000] = { 0 };

	scanf_s("%d", &n);

	for (i = 0; i < n; i++)
		scanf_s("%d", &list[i]);

	for (i = 0; i < n; i++)
	{
		a = list[i];
		index = i;
		for (j = i+1; j < n; j++)
		{
			if (a < list[j])
			{
				a = list[j];
				index = j;
			}
		}
		//已经找到非规整序列的最大值
		/*tmp = list[i];
		list[i] = list[index];
		list[index] = tmp;*/
		
		//用函数实现
		swap(list, i, index);
	}

	for(i=0;i<n;i++)
		printf("%d ", list[i]);
}

void swap(int list[], int i, int index)
{
	int tmp;

	tmp = list[i];
	list[i] = list[index];
	list[index] = tmp;
}