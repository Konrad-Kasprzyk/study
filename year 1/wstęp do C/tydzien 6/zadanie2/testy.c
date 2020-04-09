// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "testy.h"

int partition(double tablica[], int p, int r)
{
double x = tablica[p];
int i = p, j = r;
double w;
while (true)
{
while (tablica[j] > x)
j--;
while (tablica[i] < x)
i++;
if (i < j)
{
w = tablica[i];
tablica[i] = tablica[j];
tablica[j] = w;
i++;
j--;
}
else
return j;
}
}

void quicksort(double tablica[], int p, int r)
{
int q;
if (p < r)
{
q = partition(tablica,p,r);
quicksort(tablica, p, q);
quicksort(tablica, q+1, r);
}
}

int compare (const void * a, const void * b)
{
  return ( *(double*)a - *(double*)b );
}

double *generuj(int ile)
{
    double *tablica;
    tablica=malloc(ile*sizeof(double));
    srand(time(NULL));
    for (int i=0;i<ile;i++)
        *(tablica+i)=rand();
    return tablica;
}

void kopiuj(double *tab,double *gdzie,int ile)
{
    for (int i=0;i<ile;i++)
        *(gdzie+i)=*(tab+i);
}

bool czy_poprawnie(double *tab,double *wynik,int ile)
{
    int i,j,ile2,x;
    bool spr=0;
    double *tab2;
    tab2=malloc(ile*sizeof(double));
    kopiuj(tab,tab2,ile);
    ile2=ile;
    for (i=0;i<ile;i++)
    {
        for (x=0;x<ile2;x++)
        {
            if (*(tab2+x)==*(wynik+i))
            {
                spr=1;
                break;
            }
        }

        if (spr==1)
        {
            for (j=x;j<ile-1;j++)
                {
                    tab2[j]=tab2[j+1];
                }
            ile2--;
        }
        else return 0;
        spr=0;
    }
    for (int i=0;i<ile-1;i++)
        if (*(wynik+i)>*(wynik+i+1)) return 0;
return 1;

}

void czas_sortowania(int ile)
{
    double *tablica;
    int i;
    clock_t start,stop;
    double czas,sredni_czas=0,maks_czas=0,min_czas=99999999;
    for (i=0;i<100;i++)
    {
        tablica=generuj(ile);
        start=clock();
        qsort(tablica,ile,sizeof(double),compare);
        stop=clock();
        czas=(double)(stop-start) / CLOCKS_PER_SEC;
        sredni_czas+=czas;
        if (czas<min_czas) min_czas=czas;
        if (czas>maks_czas) maks_czas=czas;
        free(tablica);
    }
    printf("Sredni czas sortowania qsort dla %d elementow wynosi %f sekund\n",ile,sredni_czas/100);
    printf("Maksymalny czas sortowania qsort dla %d elementow wynosi %f sekund\n",ile,maks_czas);
    printf("Minimalny czas sortowania qsort dla %d elementow wynosi %f sekund\n",ile,min_czas);
    sredni_czas=0;
    maks_czas=0;
    min_czas=99999999;
    for (i=0;i<100;i++)
    {
        tablica=generuj(ile);
        start=clock();
        quicksort(tablica,0,ile-1);
        stop=clock();
        czas=(double)(stop-start) / CLOCKS_PER_SEC;
        sredni_czas+=czas;
        if (czas<min_czas) min_czas=czas;
        if (czas>maks_czas) maks_czas=czas;
        free(tablica);
    }
    printf("Sredni czas sortowania quicksort dla %d elementow wynosi %f sekund\n",ile,sredni_czas/100);
    printf("Maksymalny czas sortowania quicksort dla %d elementow wynosi %f sekund\n",ile,maks_czas);
    printf("Minimalny czas sortowania quicksort dla %d elementow wynosi %f sekund\n",ile,min_czas);
}
