#include <stdio.h>

#define MAX 5

// vypsani pole
void arrayPrint(int a[])
{
    for(int i = 0; i < MAX; i++)
        printf("%d, ", a[i]);

    printf("\n");
}

void binaryInsertSort(int a[])
{
    for(int i = 1; i <= MAX - 1; i++) // budeme prochazet cele pole pro kazdy prvek
    {   // nejdrive si nastavime hranice zleva a zprava pro serazenou cast
        int tmp = a[i];
        int left = 0;
        int right = i - 1;

        while(left <= right) // cyklus pro binarni vyhledavani
        {                    // hledame misto pro prvni neserazeny prvek
            int m = (left + right) / 2;

            if(tmp < a[m])
                right = m - 1;
            else
                left = m + 1;
        }

        for(int j = i - 1; j >= left; j--) // posouvame cele casti pole, abychom udelali misto pro dalsi prvek
            a[j + 1] = a[j];

        a[left] = tmp; // vlozime prvek na misto, ktere jsme pro nej udelali

        printf("binary insert iter: ");
        arrayPrint(a);
    }
}

int main()
{
    int a[MAX] = {3, 5, 7, 2, 1};

    printf("=== BINARY INSERTION SORT ===\n");

    printf("DEFAULT ARRAY:      ");
    arrayPrint(a);

    binaryInsertSort(a);

    return 0;
}
