// Konrad Kasprzyk

#include <gtk/gtk.h>

gint glosy=0,za=0,przeciw=0;

void funkcja1(GtkWidget *widget,gpointer data)
{
    char napis[50];
    glosy++;
    za++;
    gtk_button_set_label(GTK_BUTTON(widget), "ZA");    // bez tego mam błąd -Werror=unused-parametr
    sprintf(napis,"oddano glosow: %d  Za: %d%% Przeciw: %d%%",glosy,(za*100)/glosy,(przeciw*100)/glosy);
    gtk_label_set_text(GTK_LABEL(data),napis);
}
void funkcja2(GtkWidget *widget,gpointer data)
{
    char napis[50];
    glosy++;
    przeciw++;
    gtk_button_set_label(GTK_BUTTON(widget), "PRZECIW");    // bez tego mam błąd -Werror=unused-parametr
    sprintf(napis,"oddano glosow: %d  Za: %d%% Przeciw: %d%%",glosy,(za*100)/glosy,(przeciw*100)/glosy);
    gtk_label_set_text(GTK_LABEL(data),napis);
}
void funkcja3(GtkWidget *widget,gpointer data)
{
    char napis[50];
    glosy++;
    gtk_button_set_label(GTK_BUTTON(widget), "NIE MAM ZDANIA");   // bez tego mam błąd -Werror=unused-parametr
    sprintf(napis,"oddano glosow: %d  Za: %d%% Przeciw: %d%%",glosy,(za*100)/glosy,(przeciw*100)/glosy);
    gtk_label_set_text(GTK_LABEL(data),napis);
}

int main (int argc, char *argv[]) {
    GtkWidget *okno;
    GtkWidget *kontener;
    GtkWidget *przycisk1;
    GtkWidget *przycisk2;
    GtkWidget *przycisk3;
    GtkWidget *pytanie;
    GtkWidget *box1;
    GtkWidget *wynik;

    gtk_init (&argc, &argv);

    okno = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW(okno), 300, 200);
    gtk_window_set_position(GTK_WINDOW(okno), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW(okno), "Ankieta");
    gtk_container_set_border_width (GTK_CONTAINER(okno), 5);

    kontener = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(okno), kontener);

    pytanie=gtk_label_new("Czy lubisz ferie ?");
    gtk_box_pack_start(GTK_BOX(kontener), pytanie,TRUE,TRUE,0);

    box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

    przycisk1 = gtk_button_new_with_label("ZA");
    przycisk2 = gtk_button_new_with_label("PRZECIW");
    przycisk3 = gtk_button_new_with_label("NIE MAM ZDANIA");

    gtk_box_pack_start(GTK_BOX(box1), przycisk1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box1), przycisk2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box1), przycisk3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(kontener), box1,TRUE,TRUE,0);

    wynik=gtk_label_new("Wynik głosowania");
    gtk_box_pack_start(GTK_BOX(kontener), wynik,TRUE,TRUE,0);


    g_signal_connect(G_OBJECT(przycisk1), "clicked", G_CALLBACK(funkcja1),(gpointer)wynik);
    g_signal_connect(G_OBJECT(przycisk2), "clicked", G_CALLBACK(funkcja2),(gpointer)wynik);
    g_signal_connect(G_OBJECT(przycisk3), "clicked", G_CALLBACK(funkcja3),(gpointer)wynik);

    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(okno);

    gtk_main ();

    return 0;
}
