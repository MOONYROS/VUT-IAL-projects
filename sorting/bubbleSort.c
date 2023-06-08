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

// funkce bubbleSort pro pruchod zleva
void bubbleSort(int a[])
{
    int auxN = MAX; // pocita pruchody, abychom nesli za pole
    bool goOn = true;
    while((goOn == true) && (auxN > 1)) // dokud v poslednim prchodu probehlo prohozeni, pokracuj dal
    {
        goOn = false; // defaultne prohozeni neprobiha
        for(int i = 0; i < auxN - 1; i++) // prochazej pole az do konce
        {
            if(a[i + 1] < a[i]) // pokud najdes, ze prvni je prvek vetsi nez jeho nasledujici...
            {
                swap(&a[i + 1], &a[i]); // ... prohod je
                goOn = true; // a protoze probehla zmena, nastav goOn na true
            }
        }
        printf("bubbleSort iter: ");
        arrayPrint(a); // vypis retzce po kazde iteraci

        auxN = auxN - 1; // sniz pocitadlo pruchodu
    }
}

int main()
{
    int a[MAX] = {3, 5, 7, 2, 1};

    printf("=== BUBBLE SORT ===\n");

    printf("DEFAULT ARRAY:   ");
    arrayPrint(a);

    bubbleSort(a);

    return 0;
}
