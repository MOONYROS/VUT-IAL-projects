#include <stdio.h>

#define MAX 5

// struktura, diky ktere budeme moct "vracet" dve cisla
typedef struct {
    int i;
    int j;
} TIndex;

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

TIndex partition(int a[], int left, int right)
{
    int i = left; // zacneme urcenim i a j, ktere se budou posouvat proti sobe
    int j = right;
    int PM = a[(i + j) / 2]; // pseudomedian si nastavime doprostred pole

    while(i <= j) // dokud se indexy neprekrizily, posouvame i a j a provadime operace
    {
        while(a[i] < PM) // vlevo hledame prvek vetsi nebo roven pseudomedianu
            i += 1;

        while(a[j] > PM) // vpravo hledame prvek mensi nebo roven pseudomedianu
            j -= 1;

        if(i <= j) // pokud nejsou indexy prekrizene, vymenime prvky, kde se i a j zastavily
        {
            swap(&a[i], &a[j]); // vymena prvku a posunuti obou indexu
            i += 1;
            j -= 1;
        }
    }

    TIndex retIndex; // struktura pro hodnoty, co budeme vracet
    retIndex.i = i;
    retIndex.j = j;

    printf("quick sort iter: ");
    arrayPrint(a);

    return retIndex;
}

void quickSort(int a[], int left, int right)
{
    TIndex index = partition(a, left, right); // podle PM se mi rozdeli pole na 2 casti

    // podminka by tu byt nemusela, ale osetruje, ze nebudeme quickSort delat pro jednoprvkovou cast pole
    if(left < index.j)
        quickSort(a, left, index.j); // quickSort pro levou cast
    if(index.i > right)
        quickSort(a, index.j, right); // quickSort pro pravou cast
}

int main()
{
    int a[MAX] = {3, 5, 7, 2, 1};

    printf("=== QUICK SORT ===\n");

    printf("DEFAULT ARRAY:   ");
    arrayPrint(a);

    quickSort(a, 0, MAX - 1);

    return 0;
}
