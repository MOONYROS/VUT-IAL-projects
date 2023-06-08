#include <stdio.h>
#include <stdbool.h>

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

void selectSort(int a[])
{
    for(int i = 0; i < MAX - 1; i++)
    {
        int indexMin = i; // minimum nastavime vzdy na prvni prvek neserazene casti
        int min = a[i]; // a ulozime si jeho hodnotu
        for(int j = i + 1; j < MAX; j++) // prochazime pole, dokud nebude serazene
        {
            if(min > a[j]) // pokud zjistime, ze je aktualni prvek mensi, nez minimum...
            {
                min = a[j]; // ...nastavime si nove minimum
                indexMin = j; // a ulozime jeho hodnotu
            }
        }
        swap(&a[i], &a[indexMin]); // nakonec nalezene minimum prohodime s prvnim neserazenym prvkem
        
        printf("selectSort iter: ");
        arrayPrint(a);
    }
}

int main()
{
    int a[MAX] = {3, 5, 7, 2, 1};

    printf("=== SELECT SORT ===\n");

    printf("DEFAULT ARRAY:   ");
    arrayPrint(a);

    selectSort(a);

    return 0;
}
