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

void siftDown(int a[], int left, int right)
{
    int i = left;
    int j = 2 * i + 1;  // levy syn
    int temp = a[i];
    bool goOn = j <= right; // ridici promenna cyklu

    while(goOn) // dokud muzeme pokracovat...
    {
        if(j < right) // ...tak pokud ma uzel uba syny...
        {
            if(a[j] < a[j + 1]) // ...a pravy je vetsi
                j = j + 1; // tak s nim budeme pokracovat v prosevani
        }

        if(temp >= a[j]) // jestlize se pro temp naslo misto, tak koncime cyklus
            goOn = false;
        else // jinak temp prosevame niz a s a[j] pujdeme vys
        {
            a[i] = a[j];
            i = j;  // v dalsim cyklu udelame ze syna otce
            j = 2 * i + 1; // a musime tedy udelat noveho leveho syna
            goOn = j <= right; // jdeme az na posledni uroven (na list)
        }
    }
    a[i] = temp; // tohle je konecna pozice korene

    printf("array after siftdown: ");
    arrayPrint(a);
}

// funkce bubbleSort pro pruchod zleva
void heapSort(int a[])
{ // nejdrive si ustavime hromadu
    int left =  (MAX / 2) - 1; // pozice nejnizsiho nejpravejsiho otce
    int right = MAX - 1;

    for(int i = left; i >= 0; i--)
        siftDown(a, i, right);

    // vlastni cyklus heap sortu
    for(right = MAX - 1; right >= 1; right--)
    {
        swap(&a[0], &a[right]); // vymenujeme koren s aktualnim poslednim prvkem
        siftDown(a, 0, right - 1); // znovuustaveni hromady
    }
}

int main()
{
    int a[MAX] = {3, 5, 7, 2, 1};

    printf("=== HEAP SORT ===\n");

    printf("DEFAULT ARRAY:        ");
    arrayPrint(a);

    heapSort(a);

    return 0;
}
