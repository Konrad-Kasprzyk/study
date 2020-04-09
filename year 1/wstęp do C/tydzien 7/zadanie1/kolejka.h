// Konrad Kasprzyk

#ifndef KOLEJKA_H_INCLUDED
#define KOLEJKA_H_INCLUDED

#include <stdbool.h>

 typedef struct wezel *Kolejka;
    typedef struct wezel {
        double info;
        struct wezel *nast;
    } Wezel;

Kolejka utworz();
Kolejka pocz_dodaj(Kolejka wsk,double liczba);
Kolejka kon_dodaj(Kolejka wsk,double liczba);
double wyswietl_poczatek(Kolejka wsk);
double usun_i_wyswietl(Kolejka *wsk);
bool czy_pusta(Kolejka wsk);
int dlugosc_listy(Kolejka wsk);

#endif // KOLEJKA_H_INCLUDED
