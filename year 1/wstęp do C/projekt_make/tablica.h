//Konrad Kasprzyk

#ifndef FUNKCJE_H_INCLUDED
#define FUNKCJE_H_INCLUDED
#include <stdbool.h>

int biale,czarne;
char tab[10][10];
char kogo_ruch;

void inicjuj();
bool znajdz_pion(int polozenie,bool czy_gora);
bool znajdz_poziom(int polozenie,bool czy_prawo);
bool znajdz_ukos(int polozenie,bool czy_gora,bool czy_prawo);
void zamien_pion(int polozenie,bool czy_gora);
void zamien_ukos(int polozenie,bool czy_gora,bool czy_prawo);
void zamien_poziom(int polozenie,bool czy_prawo);
void wykonaj_ruch(int polozenie);
int sprawdz_ruch(int polozenie);
void tab_string(char *str);
void string_tab(char *str);

#endif // FUNKCJE_H_INCLUDED
