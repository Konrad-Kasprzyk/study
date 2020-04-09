#include <gtk/gtk.h>

int main( int argc, char *argv[])
{
    GtkWidget *okno;
    GtkWidget *vbox;

    GtkWidget *nowa_gra;
    GtkWidget *wczytaj_gre;
    GtkWidget *opcje;
    GtkWidget *autorzy;
    GtkWidget *wyjdz;

    gtk_init(&argc, &argv);

    okno = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW(okno), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size (GTK_WINDOW(okno), 230, 250);
    gtk_window_set_title (GTK_WINDOW(okno), "Gra 1.0");
    gtk_container_set_border_width (GTK_CONTAINER(okno), 5);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    /* kontener ktory ustawia widżety jeden pod drugim, te ustawienie zależy od GTK_ORIENTATION_VERTICAL, gdyby je
     * zmienić na  GTK_ORIENTATION_HORIZONTAL to by ustawiało widżety od lewej do prawej, drugi argument to odległość
     * między widżetami    */
    gtk_container_add(GTK_CONTAINER(okno), vbox);   /* vbox to nazwa kontanera, w tutorialu była
                                                     *  przestarzała funckja gtk_vbox_new   */


    nowa_gra = gtk_button_new_with_label ("Nowa gra");
    wczytaj_gre = gtk_button_new_with_label ("Wczytaj grę");
    opcje = gtk_button_new_with_label ("Opcje");
    autorzy = gtk_button_new_with_label ("Autorzy");
    wyjdz = gtk_button_new_with_label ("Wyjdź");

    gtk_box_pack_start (GTK_BOX(vbox), nowa_gra, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), wczytaj_gre, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), opcje, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), autorzy, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), wyjdz, TRUE, TRUE, 0);
    /* dodaje widżet do kontenera, pierwszy argument to kontener, drugi do widżet (przycisk), potem czy widżet ma
     * zajmować całą przestrzeń, potem czy widżet ma być rozciągnięty i ostatni argument to odległość między
     * innymi widżetami     */

    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(okno);

    gtk_main();

    return 0;
}
