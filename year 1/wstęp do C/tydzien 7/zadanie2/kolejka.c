// Konrad Kasprzyk

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "kolejka.h"
#include <stdbool.h>
#include <string.h>

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
/*
Listy_wsk lista_dodaj(Listy_wsk wsk,char napis[],Kolejka adr)
{
    Listy *nowy=(Listy*)malloc(sizeof(Listy));
    strcpy(nowy->nazwa,napis);
    nowy->adres=adr;
    if (wsk==NULL)
    {
        nowy->nast=nowy;
        return nowy;
    }
    else
    {
        Listy *pierwszy=wsk->nast;
        wsk->nast=nowy;
        nowy->nast=pierwszy;
        return wsk;
    }
}
*/
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

Listy_wsk *lista_dodaj(Listy_wsk *wsk,char napis[]) // Dodaje na koniec kolejki
{
    Listy *nowy=(Listy*)malloc(sizeof(Listy));
    Kolejka wsk_nowy;
    wsk_nowy=utworz();
    strcpy(nowy->nazwa,napis);
    nowy->adres=wsk_nowy;
    if (*wsk==NULL)
    {
        nowy->nast=nowy;
        return &nowy;
    }
    else
    {
    nowy->nast=(*wsk)->nast;
    (*wsk)->nast=nowy;
    return &nowy;
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

int ilosc_list(Listy_wsk wsk)
{
    if (wsk==NULL) return 0;
    Listy_wsk pom;
    pom=wsk->nast;
    int l=1;
    while (pom!=wsk)
    {
        pom=pom->nast;
        l++;
    }
    return l;
}

void wyswietl_listy(Listy_wsk wsk,int n)
{
    if (wsk==NULL) { printf("Nie ma list\n"); return; }
    if (n==1) { printf("1.Pierwsza lista\n"); return; }
    int i;
    wsk=wsk->nast;
    for (i=0;i<n;i++)
    {
        printf("%d. %s\n",i+1,wsk->nazwa);
        wsk=wsk->nast;
    }

}

Kolejka wybierz_liste(Listy_wsk wsk,int n)
{
    Listy_wsk pom;
    pom=wsk->nast;
    if (n==0) return NULL;
    if (n==1) return wsk->adres;
    int i;
    for (i=0;i<n;i++)
    {
        wsk=wsk->nast;
        if (pom==wsk) return NULL;
    }
    return wsk->adres;

}

char *nazwa_listy(Listy_wsk wsk,int n)
{
     int i;
    for (i=0;i<n;i++)
    {
        wsk=wsk->nast;
    }
    return wsk->nazwa;


}
