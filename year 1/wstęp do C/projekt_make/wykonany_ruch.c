//Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include "wykonany_ruch.h"
#include "tablica.h"

int sprawdz_dostepnosc_ruchu(int polozenie)
{
    int x,y;
    y=polozenie%10;
    x=polozenie/10;
    if (tab[x][y]!='p') return 0;

    if (znajdz_pion(polozenie,1)==1)    return 1;
    if (znajdz_pion(polozenie,0)==1)    return 1;
    if (znajdz_poziom(polozenie,1)==1)  return 1;
    if (znajdz_poziom(polozenie,0)==1)  return 1;
    if (znajdz_ukos(polozenie,1,1)==1)  return 1;
    if (znajdz_ukos(polozenie,1,0)==1)  return 1;
    if (znajdz_ukos(polozenie,0,1)==1)  return 1;
    if (znajdz_ukos(polozenie,0,0)==1)  return 1;

    return 0;
}

void nowa_gra()
{
    inicjuj();

    char napis[20];

    biale=2;
    czarne=2;

    gtk_text_buffer_set_text (punkty_czarne_bufor,"",-1);
    punkty_czarne_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_czarne));
    gtk_text_buffer_get_iter_at_offset(punkty_czarne_bufor, &punkty_czarne_iter, 0);
    sprintf(napis,"Czarne: %d",czarne);
    gtk_text_buffer_insert_with_tags_by_name(punkty_czarne_bufor, &punkty_czarne_iter, napis, -1, "pogrubienie","kolor", NULL);

    sprintf(napis,"Biale: %d",biale);
    gtk_text_buffer_set_text (punkty_biale_bufor,napis,-1);

    gtk_text_buffer_set_text (opis_bufor,"ruch czarnych pionkow",-1);
    gtk_text_view_set_buffer (GTK_TEXT_VIEW(opis),opis_bufor);
}

void koniec_gry()
{
    char napis[20];
    if (czarne>biale)
    {
        gtk_text_buffer_set_text (opis_bufor,"Koniec gry, wygraly pionki czarne",-1);
        gtk_text_view_set_buffer (GTK_TEXT_VIEW(opis),opis_bufor);

        gtk_text_buffer_set_text (punkty_czarne_bufor,"",-1);
        punkty_czarne_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_czarne));
        gtk_text_buffer_get_iter_at_offset(punkty_czarne_bufor, &punkty_czarne_iter, 0);
        sprintf(napis,"Czarne: %d",czarne);
        gtk_text_buffer_insert_with_tags_by_name(punkty_czarne_bufor, &punkty_czarne_iter, napis, -1, "pogrubienie","wygrana", NULL);

        sprintf(napis,"Biale: %d",biale);
        gtk_text_buffer_set_text (punkty_biale_bufor,napis,-1);

        wyswietl_komunikat("Koniec gry, wygraly pionki czarne !\nNacisnij Reset Gry, aby zaczac nowa gre");
    }
    if (czarne<biale)
    {
        gtk_text_buffer_set_text (opis_bufor,"Koniec gry, wygraly pionki biale",-1);
        gtk_text_view_set_buffer (GTK_TEXT_VIEW(opis),opis_bufor);

        gtk_text_buffer_set_text (punkty_biale_bufor,"",-1);
        punkty_biale_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_biale));
        gtk_text_buffer_get_iter_at_offset(punkty_biale_bufor, &punkty_biale_iter, 0);
        sprintf(napis,"Biale: %d",biale);
        gtk_text_buffer_insert_with_tags_by_name(punkty_biale_bufor, &punkty_biale_iter, napis, -1, "pogrubienie","wygrana", NULL);

        sprintf(napis,"Czarne: %d",czarne);
        gtk_text_buffer_set_text (punkty_czarne_bufor,napis,-1);

        wyswietl_komunikat("Koniec gry, wygraly pionki biale !\nNacisnij Reset Gry, aby zaczac nowa gre");
    }
    if (czarne==biale)
    {
        gtk_text_buffer_set_text (punkty_czarne_bufor,"",-1);
        punkty_czarne_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_czarne));
        gtk_text_buffer_get_iter_at_offset(punkty_czarne_bufor, &punkty_czarne_iter, 0);
        sprintf(napis,"Czarne: %d",czarne);
        gtk_text_buffer_insert_with_tags_by_name(punkty_czarne_bufor, &punkty_czarne_iter, napis, -1, "pogrubienie","wygrana", NULL);


        gtk_text_buffer_set_text (punkty_biale_bufor,"",-1);
        punkty_biale_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_biale));
        gtk_text_buffer_get_iter_at_offset(punkty_biale_bufor, &punkty_biale_iter, 0);
        sprintf(napis,"Biale: %d",biale);
        gtk_text_buffer_insert_with_tags_by_name(punkty_biale_bufor, &punkty_biale_iter, napis, -1, "pogrubienie","wygrana", NULL);


        wyswietl_komunikat("Koniec gry, remis !\nNacisnij Reset Gry, aby zaczac nowa gre");
    }
}

void czy_koniec()
{
char napis[20];

    if (biale+czarne>63) { koniec_gry(); return; }
    if (biale==0 || czarne==0) { koniec_gry(); return; }

    char przeciwny_kolor;
    if (kogo_ruch=='c') przeciwny_kolor='b';
    else przeciwny_kolor='c';

    kogo_ruch=przeciwny_kolor;

    int i,j;
    for (i=1;i<=8;i++)
        for (j=1;j<=8;j++)
            if (sprawdz_dostepnosc_ruchu((i*10)+j)==1)
            {
                if (kogo_ruch=='c')
                {
                    gtk_text_buffer_set_text (opis_bufor,"ruch czarnych pionkow",-1);
                    gtk_text_view_set_buffer (GTK_TEXT_VIEW(opis),opis_bufor);

                    gtk_text_buffer_set_text (punkty_czarne_bufor,"",-1);
                    punkty_czarne_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_czarne));
                    gtk_text_buffer_get_iter_at_offset(punkty_czarne_bufor, &punkty_czarne_iter, 0);
                    sprintf(napis,"Czarne: %d",czarne);
                    gtk_text_buffer_insert_with_tags_by_name(punkty_czarne_bufor, &punkty_czarne_iter, napis, -1, "pogrubienie","kolor", NULL);

                    sprintf(napis,"Biale: %d",biale);
                    gtk_text_buffer_set_text (punkty_biale_bufor,napis,-1);
                    return;
                }
                else
                {
                    gtk_text_buffer_set_text (opis_bufor,"ruch bialych pionkow",-1);
                    gtk_text_view_set_buffer (GTK_TEXT_VIEW(opis),opis_bufor);

                    gtk_text_buffer_set_text (punkty_biale_bufor,"",-1);
                    punkty_biale_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_biale));
                    gtk_text_buffer_get_iter_at_offset(punkty_biale_bufor, &punkty_biale_iter, 0);
                    sprintf(napis,"Biale: %d",biale);
                    gtk_text_buffer_insert_with_tags_by_name(punkty_biale_bufor, &punkty_biale_iter, napis, -1, "pogrubienie","kolor", NULL);

                    sprintf(napis,"Czarne: %d",czarne);
                    gtk_text_buffer_set_text (punkty_czarne_bufor,napis,-1);
                    return;

                }
            }
            if (kogo_ruch=='c')
            {
                wyswietl_komunikat("brak ruchow czarnych pionkow, ruch bialych");
                kogo_ruch='b';
            }
            else
            {
                wyswietl_komunikat("brak ruchow bialych pionkow, ruch czarnych");
                kogo_ruch='c';
            }
            for (i=1;i<=8;i++)
                for (j=1;j<=8;j++)
                    if (sprawdz_dostepnosc_ruchu((i*10)+j)==1)
                        return;

            koniec_gry();
            return;
}
