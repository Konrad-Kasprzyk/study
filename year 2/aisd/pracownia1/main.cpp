#include <iostream>
#include <stdio.h>

using namespace std;

int l;

int next_indeks(int i){
    i+=1;
 if (i==l) {
    return 0;
 }
 else return i;
}

int main()
{
    int i;
    scanf("%d",&l);
    long long int tab[l];
    for (i=0;i<l;i++)
        scanf("%lld",&tab[i]);


    if(l==2){
        if(tab[0]<tab[1])
            {
                printf("%lld",tab[0]);
                return 0;
            }
        else
            {
                printf("%lld",tab[1]);
                return 0;
            }
    }

    long long int calosc = 0;
    for (i=0;i<l;i++)
        calosc+=tab[i];


    long long int L1,L2,P1,P2;
    long long int porownaj;
    long long int najdluzsza;
    L1 = calosc - tab[0];
    P1 = tab[0];
    if (L1 > P1)
        najdluzsza = P1;
    else
        najdluzsza = L1;

    // chce sobię zachować kolejność że poprzednia długość To L1 P1

    P2 = P1 + tab[1];
    L2 = calosc - P2;

    i=2;

    while(P2<L2) // dopóki ścieżka z prawej mniejsza od lewej, czyli nie znaleźliśmy optymalnego pounktu na browar
    {
        L1 = L2;
        P1 = P2;
        P2 = P1 + tab[i];
        L2 = calosc - P2;
        i++;
    }

    if (P2 == L2){
          printf("%lld",L2);
          return 0;
        //mamy idealnie polowe odleglosci, czyli browary dalej od siebie nie moga byc ustawione, odpowiedz to L2

    }

    // mamy już te punkty P2>L2 i P1<L1 <--  nie zawsze zajdzie, na poczatku nowego browara moze nie zajsc, np mamy 3 domy po kolei od prawej 10 3 5
    if(P1<L1)
        porownaj = P1;
    else
        porownaj = L1;

    // teraz wybieramy czy dać minimum z L2 P2 czy L1 P1
  if(porownaj>L2)
    najdluzsza = porownaj;
  else
    najdluzsza = L2;


for (int j=1;j<l;j++){      // pętla od następnego domu do ostatniego

    P1-=tab[j-1];
    L1+=tab[j-1];
    P2-=tab[j-1];
    L2+=tab[j-1];

    while(P2<L2) // dopóki ścieżka z prawej mniejsza od lewej, czyli nie znaleźliśmy optymalnego punktu na browar
    {
        L1 = L2;
        P1 = P2;
        P2 = P1 + tab[i];
        L2 = calosc - P2;
        i = next_indeks(i);
    }

     if (P2 == L2){
          printf("%lld",L2);
          return 0;
        //mamy idealnie polowe odleglosci, czyli browary dalej od siebie nie moga byc ustawione, odpowiedz to L2

    }

    // mamy już te punkty P2>L2 i P1<L1 <--  nie zawsze zajdzie, na poczatku nowego browara moze nie zajsc, np mamy 3 domy po kolei od prawej 10 3 5
    if(P1<L1)
        porownaj = P1;
    else
        porownaj = L1;

    if(porownaj>L2)
    {
        if (najdluzsza<porownaj)
            najdluzsza = porownaj;
    }
    else
    {
        if (najdluzsza<L2)
            najdluzsza = L2;
    }


}

    printf("%lld",najdluzsza);
    return 0;
}
