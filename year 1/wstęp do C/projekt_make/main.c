// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#include "plansza.h"
#include "tablica.h"
#include "wykonany_ruch.h"
#include "fifo.h"

#define MAKS_DL_TEKSTU 70

static PipesPtr potoki;
static char moj_id, twoj_id;
static GtkWidget *okno;

static void przekaz_tekst();
static gboolean pobierz_tekst();
void pokazBlad(char *komunikat);
void wyswietl_komunikat(char *komunikat);
static void przeslij_dane();
static void klikniecie(GtkWidget *widget,int* data);
static void reset_gry(GtkWidget *widget);

int main( int argc, char *argv[])
{
    if ((potoki=initPipes(argc,argv)) == NULL)
        return 1;
    if (argc == 2 && strcmp(argv[1],"b") == 0) { twoj_id='c'; moj_id='b'; }
    else { moj_id='c'; twoj_id='b'; }

    GtkWidget *tabela;
    GtkWidget *reset;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *hbox2;
    GtkWidget *button;
    GtkWidget *przeslij;

    gtk_init(&argc, &argv);

    inicjuj();

    char napis[20];
    if (moj_id=='c')
    sprintf(napis,"reversi, pionki czarne");
    else
    sprintf(napis,"reversi, pionki biale");

    okno = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(okno), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(okno), 500, 500);
    gtk_window_set_title(GTK_WINDOW(okno), napis);
    gtk_container_set_border_width(GTK_CONTAINER(okno), 10);

    tabela = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(tabela), 0);
    gtk_grid_set_row_homogeneous(GTK_GRID(tabela), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(tabela), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(tabela), TRUE);

    reset=button=gtk_button_new_with_label("Reset Gry");
    g_signal_connect(G_OBJECT(reset), "clicked", G_CALLBACK(reset_gry),NULL);
    przeslij=button=gtk_button_new_with_label("Przeslij Dane");
    g_signal_connect(G_OBJECT(przeslij), "clicked", G_CALLBACK(przeslij_dane),NULL);

    int i,a=0,b=0;
    for (i=0;i<64;i++)
    {
        button=gtk_button_new();
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(klikniecie),&tab_przycisk[i].pozycja);
        gtk_grid_attach(GTK_GRID(tabela), button, tab_przycisk[i].posX, tab_przycisk[i].posY, tab_przycisk[i].lenX, tab_przycisk[i].lenY);
        dane_przyciskow.tablica_buttonow[a][b]=GTK_BUTTON(button);
        dane_przyciskow.zeszly_pionek[a][b]='p';
        b++;
        if (b==8) { a++; b=0; }
    }

    ustaw_poczatkowe_pionki();

    opis = gtk_text_view_new();
    opis_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(opis));
    gtk_text_buffer_set_text (opis_bufor,"ruch czarnych pionkow",-1);
    gtk_text_view_set_buffer (GTK_TEXT_VIEW(opis),opis_bufor);

    sprintf(napis,"Biale: %d",biale);
    punkty_biale = gtk_text_view_new();
    punkty_biale_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_biale));
    gtk_text_buffer_set_text (punkty_biale_bufor,napis,-1);
    gtk_text_view_set_buffer (GTK_TEXT_VIEW(punkty_biale),punkty_biale_bufor);

    sprintf(napis,"Czarne: %d",czarne);
    punkty_czarne = gtk_text_view_new();
    punkty_czarne_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_czarne));
    gtk_text_buffer_set_text (punkty_czarne_bufor,napis,-1);
    gtk_text_view_set_buffer (GTK_TEXT_VIEW(punkty_czarne),punkty_czarne_bufor);

    gtk_text_view_set_editable (GTK_TEXT_VIEW(opis),0);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(opis),0);
    gtk_text_view_set_editable (GTK_TEXT_VIEW(punkty_biale),0);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(punkty_biale),0);
    gtk_text_view_set_editable (GTK_TEXT_VIEW(punkty_czarne),0);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(punkty_czarne),0);

    gtk_text_buffer_create_tag(punkty_biale_bufor, "kolor", "foreground", "brown", NULL);
    gtk_text_buffer_create_tag(punkty_czarne_bufor, "kolor", "foreground", "brown", NULL);
    gtk_text_buffer_create_tag(punkty_biale_bufor, "pogrubienie", "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(punkty_czarne_bufor, "pogrubienie", "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(punkty_biale_bufor, "wygrana", "foreground", "red", NULL);
    gtk_text_buffer_create_tag(punkty_czarne_bufor, "wygrana", "foreground", "red", NULL);

    gtk_text_buffer_set_text (punkty_czarne_bufor,"",-1);
    punkty_czarne_bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(punkty_czarne));
    gtk_text_buffer_get_iter_at_offset(punkty_czarne_bufor, &punkty_czarne_iter, 0);
    sprintf(napis,"Czarne: %d",czarne);
    gtk_text_buffer_insert_with_tags_by_name(punkty_czarne_bufor, &punkty_czarne_iter, napis, -1, "pogrubienie","kolor", NULL);

    gtk_text_view_set_justification (GTK_TEXT_VIEW(opis),GTK_JUSTIFY_CENTER);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(punkty_biale),GTK_JUSTIFY_CENTER);
    gtk_text_view_set_justification (GTK_TEXT_VIEW(punkty_czarne),GTK_JUSTIFY_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_box_pack_start (GTK_BOX(hbox), punkty_biale, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(hbox), punkty_czarne, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(hbox2), reset, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(hbox2), przeslij, TRUE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX(vbox), opis, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), tabela, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), hbox2, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(okno), vbox);

    g_timeout_add(100,pobierz_tekst,NULL);
    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(okno);

    gtk_main();

    return 0;
}

void pokazBlad(char *komunikat)
{
    GtkWidget *dialog;
    dialog=gtk_message_dialog_new (GTK_WINDOW(okno),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"%s",komunikat);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void wyswietl_komunikat(char *komunikat)
{
    GtkWidget *dialog;
    dialog=gtk_message_dialog_new(GTK_WINDOW(okno),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER,GTK_BUTTONS_OK,"%s",komunikat);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void przeslij_dane()
{
    gchar napis[MAKS_DL_TEKSTU];
    tab_string(napis);

    if (napis[0]=='b') napis[0]='c';
    else napis[0]='b';
    sendStringToPipe(potoki, napis);
}

static void klikniecie(GtkWidget *widget,int* data)
{
    widget=widget;         // bez tego mam blad -Werror

    if (kogo_ruch!=moj_id) return;
    if (sprawdz_ruch(*data)==0) return;
    przekaz_tekst();
    podstaw_plansze();
    czy_koniec();
}

static void reset_gry(GtkWidget *widget)
{
    widget=widget;      // bez tego mam blad -Werror
    gchar napis[MAKS_DL_TEKSTU];

    tab_string(napis);
    napis[0]='r';
    sendStringToPipe(potoki,napis);
    nowa_gra();
    podstaw_plansze();
}

static void przekaz_tekst()
{
    gchar napis[MAKS_DL_TEKSTU];

    tab_string(napis);
    sendStringToPipe(potoki, napis);
}

static gboolean pobierz_tekst()
{
  gchar napis[MAKS_DL_TEKSTU];

  if (getStringFromPipe(potoki,napis,MAKS_DL_TEKSTU)) {
        if (napis[0]=='r') { nowa_gra(); podstaw_plansze(); return TRUE; }
        string_tab(napis);
        podstaw_plansze();
        czy_koniec();
  }
  return TRUE;
}
