// Konrad Kasprzyk

#ifndef WLLC_H_INCLUDED
#define WLLC_H_INCLUDED

#include<stdbool.h>

typedef struct wezel *WLLC;
typedef struct wezel{
struct wezel *nast;
bool czy_liczba;
int liczba;
struct wezel *podlista;
}Wezel;

WLLC utworz();
WLLC dl(int liczba,WLLC wsk);
WLLC dp(WLLC podlista,WLLC wsk);
void drukuj(WLLC wsk);

WLLC dopisz_koniec(int liczba,WLLC *wsk);
WLLC kopiuj(WLLC wsk);
WLLC polacz(WLLC wsk,WLLC cel);
WLLC WLLC_merge(WLLC gdzie,WLLC dolacz);
WLLC WLLC_flat(WLLC wskaznik);

#endif // WLLC_H_INCLUDED
