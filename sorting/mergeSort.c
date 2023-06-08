#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// vypsani pole
void arrayPrint(int a[])
{
    for(int i = 0; i < MAX; i++)
        printf("%d, ", a[i]);

    printf("\n");
}

void merge(int a[], int left, int mid, int right)
{
    int leftCount = mid - left + 1; // zjitime si pocet prvku napravo i nalevo
    int rightCount = right - mid;

    /** NEVSIMEJTE SI CHYBY, PROGRAMU VADI, ZE LEFTCOUNT A RIGHTCOUNT NEMUSI BYT KONSTANTY **/
    int L[leftCount];   // dve pomocna pole pro levou a pravou cast
    int R[rightCount];

    for(int i = 0; i <= leftCount - 1; i++) // obe posloupnosti si dame do pomocneho pole (po jednom prvku)
        L[i] = a[left + i];

    for(int j = 0; j <= rightCount - 1; j++)
        R[j] = a[mid + 1 + j];

    #ifdef _WIN32 // zjisteni, na jakem systemu se nachazime (Windows/Unix), makra se lisi podle systemu
        L[leftCount] = INT_MAX; // nastaveni zarazek vpravo i vlevo
        R[rightCount] = INT_MAX;
    #elif __unix__
        L[leftCount] = __INT_MAX__;
        R[rightCount] = __INT_MAX__;
    #elif __APPLE__
        L[leftCount] = __INT_MAX__;
        R[rightCount] = __INT_MAX__;
    #endif

    int i = 0;
    int j = 0;

    for(int k = left; k <= right; k++) // zacneme spojovat pole
    { // hledame mensi prvek
        if(L[i] <= R[j]) // byl v leve posloupnosti
        {
            a[k] = L[i]; // tento prvek dame do pole na sve misto
            i = i + 1; // posuneme se na dalsi prvek
        }
        else // byl v prave posloupnosti
        {
            a[k] = R[j]; // zde probiha to same, jenom pro pravou stranu
            j = j+ 1;
        }
    }
}

void mergeSort(int a[], int left, int right)
{
    if(left < right) // overime si, ze jsou kraje spravne
    {
        int q = (left + right) / 2; // rozdelime si pole na 2 casti
        mergeSort(a, left, q); // pro obe casti zavolame rekurzivne mergesort
        mergeSort(a, q+1, right);
        merge(a, left, q, right); // casti nakonec slepime dohromady

        printf("merge sort iter: ");
        arrayPrint(a);
    }
}

int main()
{
    int a[MAX] = {3, 7, 5, 2, 1};

    printf("=== MERGE SORT ===\n");

    printf("DEFAULT ARRAY:   ");
    arrayPrint(a);

    mergeSort(a, 0, MAX - 1);

    return 0;
}
