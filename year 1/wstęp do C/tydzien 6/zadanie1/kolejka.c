//Konrad Kasprzyk

#include <stdlib.h>
#include <stdio.h>
#include "kolejka.h"


void inicjalizacja()
{
    tablica=(double*)malloc(4*sizeof(double));
    poczatek=tablica;
    koniec=tablica-1; // poza przedziałem gdy pusty
}

void dopisz(double dop)
{
    if (koniec-poczatek<0) { *tablica=dop; koniec=poczatek; return; }
    if (koniec==(tablica+3)) return;
    koniec++;
    *koniec=dop;
}

void wypisz()
{
    if (koniec-poczatek<0) return;
    double x;
    x=*poczatek;
    for (int i=0;i<koniec-poczatek;i++)
        *(tablica+i)=*(tablica+i+1);
    koniec--;
    printf("%f",x);
}

void oproznij()
{
    koniec=tablica-1;
}

bool czy_pusty()
{
    if (koniec-poczatek<0) return true;
    else return false;
}
