#include <stdio.h>

#define MAX 8

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

int partition2(int a[], int left, int right)
{
    int i = left - 1;
    int PM = a[right]; // ustaveni pseudomedianu (nejpravejsi prvek)

    for(int j = left; j <= right - 1; j++) // prochazeni pole zleva
    {
        if(a[j] <= PM) // pokud najdeme prvek mensi nez pseudomedian, posleme ho do leve casti
        {
            i = i + 1; // za posledni prvek
            swap(&a[i], &a[j]); // prohodime nalezene prvky
        }
    }
    swap(&a[i + 1], &a[right]);

    printf("quick sort 2 iter: ");
    arrayPrint(a);

    return i + 1;
}

void quickSort2(int a[], int left, int right)
{
    if(left < right)
    {
        int q = partition2(a, left, right);
        quickSort2(a, left, q - 1); // rekurze leve casti
        quickSort2(a, q + 1, right); // rekurze prave casti
    }
}

int main()
{
    int a[MAX] = {2, 8, 7, 1, 3, 5, 6, 4};

    printf("=== QUICK SORT 2 ===\n");

    printf("DEFAULT ARRAY:     ");
    arrayPrint(a);

    quickSort2(a, 0, MAX - 1);

    return 0;
}
