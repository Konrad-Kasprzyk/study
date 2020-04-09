//Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"
#include "tablica.h"

static GtkWidget *obraz_bialy;
static GtkWidget *obraz_czarny;
static GdkPixbuf *pixbuf;

struct przycisk tab_przycisk[64]={
{11,0,1,0,1},{12,1,1,0,1},{13,2,1,0,1},{14,3,1,0,1},{15,4,1,0,1},{16,5,1,0,1},{17,6,1,0,1},{18,7,1,0,1},
{21,0,1,1,1},{22,1,1,1,1},{23,2,1,1,1},{24,3,1,1,1},{25,4,1,1,1},{26,5,1,1,1},{27,6,1,1,1},{28,7,1,1,1},
{31,0,1,2,1},{32,1,1,2,1},{33,2,1,2,1},{34,3,1,2,1},{35,4,1,2,1},{36,5,1,2,1},{37,6,1,2,1},{38,7,1,2,1},
{41,0,1,3,1},{42,1,1,3,1},{43,2,1,3,1},{44,3,1,3,1},{45,4,1,3,1},{46,5,1,3,1},{47,6,1,3,1},{48,7,1,3,1},
{51,0,1,4,1},{52,1,1,4,1},{53,2,1,4,1},{54,3,1,4,1},{55,4,1,4,1},{56,5,1,4,1},{57,6,1,4,1},{58,7,1,4,1},
{61,0,1,5,1},{62,1,1,5,1},{63,2,1,5,1},{64,3,1,5,1},{65,4,1,5,1},{66,5,1,5,1},{67,6,1,5,1},{68,7,1,5,1},
{71,0,1,6,1},{72,1,1,6,1},{73,2,1,6,1},{74,3,1,6,1},{75,4,1,6,1},{76,5,1,6,1},{77,6,1,6,1},{78,7,1,6,1},
{81,0,1,7,1},{82,1,1,7,1},{83,2,1,7,1},{84,3,1,7,1},{85,4,1,7,1},{86,5,1,7,1},{87,6,1,7,1},{88,7,1,7,1}
};

void ustaw_poczatkowe_pionki()
{
    pixbuf=gdk_pixbuf_new_from_file("bialy.jpg",NULL);
    pixbuf=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    obraz_bialy=gtk_image_new_from_pixbuf(pixbuf);

    gtk_button_set_image(GTK_BUTTON(dane_przyciskow.tablica_buttonow[3][3]),obraz_bialy);

    pixbuf=gdk_pixbuf_new_from_file("czarny.png",NULL);
    pixbuf=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    obraz_czarny=gtk_image_new_from_pixbuf(pixbuf);

    gtk_button_set_image(GTK_BUTTON(dane_przyciskow.tablica_buttonow[3][4]),obraz_czarny);

    pixbuf=gdk_pixbuf_new_from_file("czarny.png",NULL);
    pixbuf=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    obraz_czarny=gtk_image_new_from_pixbuf(pixbuf);

    gtk_button_set_image(GTK_BUTTON(dane_przyciskow.tablica_buttonow[4][3]),obraz_czarny);

    pixbuf=gdk_pixbuf_new_from_file("bialy.jpg",NULL);
    pixbuf=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    obraz_bialy=gtk_image_new_from_pixbuf(pixbuf);

    gtk_button_set_image(GTK_BUTTON(dane_przyciskow.tablica_buttonow[4][4]),obraz_bialy);

    dane_przyciskow.zeszly_pionek[3][3]='b';
    dane_przyciskow.zeszly_pionek[3][4]='c';
    dane_przyciskow.zeszly_pionek[4][3]='c';
    dane_przyciskow.zeszly_pionek[4][4]='b';
}

void podstaw_plansze()
{
    int i,j;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            if (tab[i+1][j+1]!=dane_przyciskow.zeszly_pionek[i][j])
            {
                if (tab[i+1][j+1]=='b')
                {
                    pixbuf=gdk_pixbuf_new_from_file("bialy.jpg",NULL);
                    pixbuf=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
                    obraz_bialy=gtk_image_new_from_pixbuf(pixbuf);

                    gtk_button_set_image(GTK_BUTTON(dane_przyciskow.tablica_buttonow[i][j]),obraz_bialy);

                    dane_przyciskow.zeszly_pionek[i][j]=tab[i+1][j+1];
                }
                if (tab[i+1][j+1]=='c')
                {
                    pixbuf=gdk_pixbuf_new_from_file("czarny.png",NULL);
                    pixbuf=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
                    obraz_czarny=gtk_image_new_from_pixbuf(pixbuf);

                    gtk_button_set_image(GTK_BUTTON(dane_przyciskow.tablica_buttonow[i][j]),obraz_czarny);

                    dane_przyciskow.zeszly_pionek[i][j]=tab[i+1][j+1];
                }
                if (tab[i+1][j+1]=='p')
                {
                    gtk_button_set_image(GTK_BUTTON(dane_przyciskow.tablica_buttonow[i][j]),NULL);

                    dane_przyciskow.zeszly_pionek[i][j]=tab[i+1][j+1];
                }
            }
}
