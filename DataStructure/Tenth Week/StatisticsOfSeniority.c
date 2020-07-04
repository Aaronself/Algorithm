#include <stdio.h>

int count[51] = {0};

int main()
{
    int i, j, N;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf(" %d", &j);
        count[j]++;
    }

    for (i = 0; i <= 50; i++)
    {
        if(count[i] != 0)
            printf("%d:%d\n", i, count[i]);
    }
}