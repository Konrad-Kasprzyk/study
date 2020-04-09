// Konrad Kasprzyk

#ifndef KOLEJKA_H_INCLUDED
#define KOLEJKA_H_INCLUDED

#include <stdbool.h>

 typedef struct wezel *Kolejka;
    typedef struct wezel {
        double info;
        struct wezel *nast;
    } Wezel;

    typedef struct listy *Listy_wsk;
    typedef struct listy {
        char nazwa[30];
        Kolejka adres;
        struct listy *nast;
    } Listy;

Kolejka utworz();
Kolejka pocz_dodaj(Kolejka wsk,double liczba);
Kolejka kon_dodaj(Kolejka wsk,double liczba);
double wyswietl_poczatek(Kolejka wsk);
double usun_i_wyswietl(Kolejka *wsk);
bool czy_pusta(Kolejka wsk);
int dlugosc_listy(Kolejka wsk);
Listy_wsk *lista_dodaj(Listy_wsk *wsk,char napis[]);
int ilosc_list(Listy_wsk wsk);
void wyswietl_listy(Listy_wsk wsk,int n);
Kolejka wybierz_liste(Listy_wsk wsk,int n);
char *nazwa_listy(Listy_wsk wsk,int n);

#endif // KOLEJKA_H_INCLUDED
