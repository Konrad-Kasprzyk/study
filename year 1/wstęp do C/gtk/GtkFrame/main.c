#include <gtk/gtk.h>

int main( int argc, char *argv[])
{
    GtkWidget *okno;
    GtkWidget *tabela;
    GtkWidget *ramka1;
    GtkWidget *ramka2;
    GtkWidget *ramka3;
    GtkWidget *ramka4;

    GtkWidget *vbox;
    GtkWidget *nowa_gra;
    GtkWidget *wczytaj_gre;

    gtk_init(&argc, &argv);

    okno = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(okno), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(okno), 250, 250);
    gtk_window_set_title(GTK_WINDOW(okno), "GtkFrame");

    gtk_container_set_border_width(GTK_CONTAINER(okno), 10);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    tabela = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(tabela), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(tabela), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(tabela), 5);
    gtk_grid_set_column_homogeneous(GTK_GRID(tabela), TRUE);
    gtk_container_add(GTK_CONTAINER(okno), tabela);

    ramka1 = gtk_frame_new("GTK_SHADOW_IN");
    gtk_frame_set_shadow_type(GTK_FRAME(ramka1), GTK_SHADOW_IN);
    ramka2 = gtk_frame_new("GTK_SHADOW_OUT");
    gtk_frame_set_shadow_type(GTK_FRAME(ramka2), GTK_SHADOW_OUT);
    ramka3 = gtk_frame_new("GTK_SHADOW_ETCHED_IN");
    gtk_frame_set_shadow_type(GTK_FRAME(ramka3), GTK_SHADOW_ETCHED_IN);
    ramka4 = gtk_frame_new("GTK_SHADOW_ETCHED_OUT");
    gtk_frame_set_shadow_type(GTK_FRAME(ramka4), GTK_SHADOW_ETCHED_OUT);

    gtk_grid_attach(GTK_GRID(tabela), ramka1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tabela), ramka2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(tabela), ramka3, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tabela), ramka4, 1, 1, 1, 1);

    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);


    nowa_gra = gtk_button_new_with_label ("Nowa gra");
    wczytaj_gre = gtk_button_new_with_label ("Wczytaj grę");
    gtk_box_pack_start (GTK_BOX(vbox), nowa_gra, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), wczytaj_gre, TRUE, TRUE, 0);

   // gtk_box_pack_start(GTK_BOX(ramka1), vbox, TRUE, TRUE, 10);
  //  gtk_container_add(GTK_CONTAINER(ramka1), vbox);
  //  gtk_container_add(GTK_CONTAINER(ramka2), vbox);
    gtk_container_add(GTK_CONTAINER(ramka3), vbox);
  //  gtk_container_add(GTK_CONTAINER(ramka4), vbox);

    gtk_widget_show_all(okno);

    gtk_main();

    return 0;
}
