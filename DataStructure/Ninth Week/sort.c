#include <stdio.h>

void MergeSort(int list[], int tmplist[], int left, int right);
void Merge(int list[], int tmplist[], int left, int mid, int right);
int main()
{
    int i, N, index = 0;
    int list[100000], tmplist[100000];

    scanf("%d",&N);
    for(i=0; i<N; i++)
        scanf(" %d", &list[index++]);
    
    MergeSort(list, tmplist, 0, N-1);

    for(i=0; i<N; i++)
    {
        printf("%d", list[i]);
        if(i != N-1)
            printf(" ");
    }
}

void MergeSort(int list[], int tmplist[], int left, int right)
{
    int mid;
    
    if(left >= right) return;
    mid = (left + right) / 2;
    MergeSort(list, tmplist, left, mid);
    MergeSort(list, tmplist, mid+1, right);
    Merge(list, tmplist, left, mid, right);
}

void Merge(int list[], int tmplist[], int left, int mid, int right)
{
    int i, j, k;

    i = left;
    j = mid + 1;
    k = 0;
    while(i <= mid && j <= right)
    {
        if(list[i] < list[j])
        {
            tmplist[left + k] = list[i];
            k++;
            i++;
        }
        else if(list[i] >= list[j])
        {
            tmplist[left + k] = list[j];
            k++;
            j++;
        }
    }

    while(i <= mid)
    {
        tmplist[left + k] = list[i];
        k++;
        i++;
    }
    while(j <= right)
    {
        tmplist[left + k] = list[j];
        k++;
        j++;
    }

    for(i = left; i <= right; i++)
        list[i] = tmplist[i];
}