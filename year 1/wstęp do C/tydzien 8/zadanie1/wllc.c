// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include "wllc.h"

WLLC utworz()
{
    return NULL;
}

WLLC dl(int liczba,WLLC wsk)
{
    WLLC nowy=(WLLC)malloc(sizeof(Wezel));
    nowy->czy_liczba=1;
    nowy->liczba=liczba;
    nowy->nast=wsk;
    return nowy;

}

WLLC dp(WLLC podlista,WLLC wsk)
{
    WLLC nowy=(WLLC)malloc(sizeof(Wezel));
    nowy->czy_liczba=0;
    nowy->podlista=podlista;
    nowy->nast=wsk;
    return nowy;

}

void drukuj(WLLC wsk)
{
    printf(("["));
    for(WLLC p=wsk;p!=NULL;p=p->nast)
    {
        if(p->czy_liczba==1)  printf("%d",p->liczba);
        else drukuj(p->podlista);
        if (p->nast!=NULL) printf(",");
    }
    printf(("]"));
}

WLLC kopiuj(WLLC wsk)
{
    if (wsk==NULL) return NULL;
    else
    {
        WLLC nowy=(WLLC)malloc(sizeof(Wezel));
        if (wsk->czy_liczba==1)
        {
            nowy->czy_liczba=1;
            nowy->liczba=wsk->liczba;
        }
        else
        {
            nowy->czy_liczba=0;
            nowy->podlista=wsk->podlista;
        }
        nowy->nast=kopiuj(wsk->nast);
        return nowy;
    }
}

WLLC polacz(WLLC wsk,WLLC cel)
{
    if (wsk==NULL) return cel;
    wsk->nast=polacz(wsk->nast,cel);
    return wsk;
}

WLLC WLLC_merge(WLLC gdzie,WLLC dolacz)
{
    WLLC L1,L2;
    L1=kopiuj(gdzie);
    L2=kopiuj(dolacz);
    if (gdzie==NULL) return L2;
    if (dolacz==NULL) return L1;
    L1=polacz(L1,L2);
    return L1;
}

WLLC dopisz_koniec(int liczba,WLLC *wsk)
{
    WLLC nowy=(WLLC)malloc(sizeof(Wezel));
    WLLC poczatek=(*wsk);
    if ((*wsk)==NULL)
    {
       return dl(liczba,(*wsk));
    }
    while((*wsk)->nast!=NULL)
    {
        (*wsk)=(*wsk)->nast;
    }
    nowy->czy_liczba=1;
    nowy->liczba=liczba;
    nowy->nast=NULL;
    (*wsk)->nast=nowy;
    return poczatek;
}


WLLC WLLC_flat(WLLC wsk)
{
    WLLC stworz,poprzednik;
    poprzednik=utworz();
    stworz=utworz();
     WLLC pierwszy;
    pierwszy=utworz();
    skok:
    if (wsk==NULL) return wsk;
     if(wsk->czy_liczba==1)
        {
            stworz=(WLLC)malloc(sizeof(Wezel));
            stworz=utworz();
            stworz=dopisz_koniec(wsk->liczba,&stworz);
            wsk=wsk->nast;
            pierwszy=stworz;
            poprzednik=stworz;
        }
    else
        {
            if (wsk->nast==NULL) return NULL;
            stworz=WLLC_merge(stworz,WLLC_flat(wsk->podlista));
            pierwszy=stworz;
            poprzednik=stworz;
           while(stworz->nast!=NULL)
                {
                    stworz=stworz->nast;
                    poprzednik->nast=stworz;
                    poprzednik=stworz;
                }

             wsk=wsk->nast;
        }
        if (stworz==NULL)  goto skok;
    while(wsk!=NULL)
    {
          if(wsk->czy_liczba==1)
        {
            stworz=(WLLC)malloc(sizeof(Wezel));
            stworz=utworz();
            stworz=dopisz_koniec(wsk->liczba,&stworz);
            poprzednik->nast=stworz;
            poprzednik=stworz;
        }

        else
            {
                stworz=WLLC_merge(stworz,WLLC_flat(wsk->podlista));
                 while(stworz->nast!=NULL)
                 {
                    stworz=stworz->nast;
                    poprzednik->nast=stworz;
                    poprzednik=stworz;
                 }
            }

             wsk=wsk->nast;
    }

    stworz->nast=NULL;

return pierwszy;
}
