/*
解题思路：
仅靠交换0号元素，不考虑时间复杂度的情况，用一个数组完成
每次交换0和0下标的数字，若0被交换到数组第一个，再判断是否有其他元素不在正确位置，
考虑时间复杂度
用空间换时间，再建一个数组，即：下标：存储的数字 内容：存储的数字在list数组中的位置
*/
#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 100000

int SortCnt(int index_0, int N);
void swap(int a, int b);

int list[MAXSIZE];
int store[MAXSIZE];

int main()
{
    int i, index_0 = 0, N;
    int count = 0;

    scanf("%d", &N);
    if(N == 0)
    {
        printf("0"); return 0;
    }
    for (i = 0; i < N; i++)
    {
        scanf(" %d", &list[i]);
        if(list[i] == 0) index_0 = i;
        store[list[i]] = i;
    }
    count = SortCnt(index_0, N);
    printf("%d", count);

    return 0;
}

int SortCnt(int index_0, int N)
{
    int i, j, tmp;
    int count = 0;

    for(i = 0; i < N; i++) {
        if(i != list[i]) {
            while(list[0] != 0) {
                j = store[index_0];
                swap(index_0, j);
                index_0 = j;
                count++;
            }
            if(i != list[i]) {
                swap(index_0, i);
                index_0 = i;
                count++;
            }
        }
    }
    return count;
}

void swap(int a, int b)
{
    int i, tmp = 0;

    tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;

    tmp = store[list[a]];
    store[list[a]] = store[list[b]];
    store[list[b]] = tmp;

    for (i = 0; i < 10; i++)
        printf("%d ", list[i]);
    printf("\n");
}