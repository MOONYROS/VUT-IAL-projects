#include <stdio.h>

#define MAX 5

// prohozeni cisel
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// vypsani pole
void arrayPrint(int a[])
{
    for(int i = 0; i < MAX; i++)
        printf("%d, ", a[i]);

    printf("\n");
}

void shellSort(int a[])
{
    int step = MAX / 2;
    while(step > 0)
    {
        for(int i = step; i <= MAX - 1; i++)
        {
            int j = i - step;
            while((j >= 0) && (a[j] > a[j + step]))
            {
                swap(&a[j], &a[j + step]);
                j = j - step;
            }
        }
        step = step / 2;

        printf("shell sort iter: ");
        arrayPrint(a);
    }
}

int main()
{
    int a[MAX] = {3, 5, 7, 2, 1};

    printf("=== SHELL SORT ===\n");

    printf("DEFAULT ARRAY:   ");
    arrayPrint(a);

    shellSort(a);

    return 0;
}
