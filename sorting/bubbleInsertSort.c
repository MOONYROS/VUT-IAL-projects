#include <stdio.h>
#include <stdbool.h>

#define MAX 5

// vypsani pole
void arrayPrint(int a[])
{
    for(int i = 0; i < MAX; i++)
        printf("%d, ", a[i]);
    
    printf("\n");
}

void bubbleInsertSort(int a[])
{
    for(int i = 1; i < MAX; i++)
    {
        int tmp = a[i]; // vytvorime si nahradni prvek, kterym budeme prepisovat
        int j = i - 1; // a budeme si uchovavat pozici pred nim
        while((j >= 0) && (tmp < a[j])) // jestli je aktualni prvek mensi nez predchozi...
        {
            a[j + 1] = a[j]; // ...tak je vsechny presuneme...
            j = j - 1;
        }
        a[j + 1] = tmp; // ...a aktualni prvek dame na sve misto

        printf("bubble insert iter: ");
        arrayPrint(a);
    }
}

int main()
{
    int a[MAX] = {3, 5, 7, 2, 1};

    printf("=== BUBBLE INSERTION SORT ===\n");

    printf("DEFAULT ARRAY:      ");
    arrayPrint(a);

    bubbleInsertSort(a);

    return 0;
}
