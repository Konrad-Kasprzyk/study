// Konrad Kasprzyk

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "kolejka.h"
#include <stdbool.h>

Kolejka utworz()
{
    Kolejka wsk=NULL;
    return wsk;
}

Kolejka pocz_dodaj(Kolejka wsk,double liczba)
{
    Wezel *nowy=(Wezel*)malloc(sizeof(Wezel));
    nowy->info=liczba;
    if (wsk==NULL)
    {
        nowy->nast=nowy;
        return nowy;
    }
    else
    {
        Wezel *pierwszy=wsk->nast;
        wsk->nast=nowy;
        nowy->nast=pierwszy;
        return wsk;
    }
}

Kolejka kon_dodaj(Kolejka wsk,double liczba)
{
    Wezel *nowy=(Wezel*)malloc(sizeof(Wezel));
    nowy->info=liczba;
    if (wsk==NULL)
    {
        nowy->nast=nowy;
        return nowy;
    }
    else
    {
    nowy->nast=wsk->nast;
    wsk->nast=nowy;
    return nowy;
    }
}

double wyswietl_poczatek(Kolejka wsk)
{
    if (wsk==NULL)  return NAN;
    else
    return wsk->nast->info;

}

double usun_i_wyswietl(Kolejka *wsk)
{
double a;
Kolejka pierwszy;
    if ((*wsk)==NULL) return NAN;

    else
    {
   a=(*wsk)->nast->info;
    if ((*wsk)==(*wsk)->nast)
        {
            free((*wsk));
            (*wsk)=NULL;
        }
    else
        {
            pierwszy=(*wsk)->nast;
            (*wsk)->nast=(*wsk)->nast->nast;
            free(pierwszy);
        }
     }
     return a;
}

bool czy_pusta(Kolejka wsk)
{
    if (wsk==NULL) return 1;
    else return 0;
}

int dlugosc_listy(Kolejka wsk)
{
    if (wsk==NULL) return 0;
    Kolejka pom;
    pom=wsk->nast;
    int l=1;
    while (pom!=wsk)
    {
        pom=pom->nast;
        l++;
    }
    return l;
}
