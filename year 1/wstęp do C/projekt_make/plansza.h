//Konrad Kasprzyk

#ifndef PLANSZA_H_INCLUDED
#define PLANSZA_H_INCLUDED
#include <gtk/gtk.h>

struct button_struct{
GtkButton *tablica_buttonow[8][8];
char zeszly_pionek[8][8];
};

struct button_struct dane_przyciskow;

struct przycisk{
int pozycja;
int posX,lenX,posY,lenY;
};

struct przycisk tab_przycisk[64];

void podstaw_plansze();
void ustaw_poczatkowe_pionki();

#endif // PLANSZA_H_INCLUDED
