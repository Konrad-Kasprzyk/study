//Konrad Kasprzyk

#ifndef WYKONANY_RUCH_H_INCLUDED
#define WYKONANY_RUCH_H_INCLUDED
#include <gtk/gtk.h>

    GtkWidget *opis;
    GtkTextBuffer *opis_bufor;
    GtkWidget *punkty_biale;
    GtkTextBuffer *punkty_biale_bufor;
    GtkTextIter punkty_biale_iter;
    GtkWidget *punkty_czarne;
    GtkTextBuffer *punkty_czarne_bufor;
    GtkTextIter punkty_czarne_iter;

    int sprawdz_dostepnosc_ruchu(int polozenie);
    void czy_koniec();
    void wyswietl_komunikat(char *komunikat);
    void nowa_gra();
    void koniec_gry();

#endif // WYKONANY_RUCH_H_INCLUDED
