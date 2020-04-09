#include <gtk/gtk.h>

int main( int argc, char *argv[])
{
    GtkWidget *okno;

    GtkWidget *tabela;
    GtkWidget *przycisk[16];

    gtk_init(&argc, &argv);

    okno = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(okno), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(okno), 250, 180);
    gtk_window_set_title(GTK_WINDOW(okno), "Kurs GTK+");

    gtk_container_set_border_width(GTK_CONTAINER(okno), 5);

    tabela = gtk_grid_new(); // tworzy kontener na widżety ustawiane jak w tabeli w różnych pozycjach o różnej wielkości
    gtk_grid_set_row_spacing(GTK_GRID(tabela), 5); // ustawia odległość między widżetami góra dół
    gtk_grid_set_row_homogeneous(GTK_GRID(tabela), TRUE); // dzięki temu odległość góra dół dostosuje sie do rozmiaru okna
    gtk_grid_set_column_spacing(GTK_GRID(tabela), 5); // ustawia odległość między widżetami lewo prawo
    gtk_grid_set_column_homogeneous(GTK_GRID(tabela), TRUE); // odległość lewo prawo dostosuje sie do rozmiaru okna
   // gtk_box_pack_start(GTK_BOX(okno), tabela, TRUE, TRUE, 0);

    przycisk[0] = gtk_button_new_with_label ("7");
    przycisk[1] = gtk_button_new_with_label ("8");
    przycisk[2] = gtk_button_new_with_label ("9");
    przycisk[3] = gtk_button_new_with_label ("/");

    przycisk[4] = gtk_button_new_with_label ("4");
    przycisk[5] = gtk_button_new_with_label ("5");
    przycisk[6] = gtk_button_new_with_label ("6");
    przycisk[7] = gtk_button_new_with_label ("*");

    przycisk[8] = gtk_button_new_with_label ("1");
    przycisk[9] = gtk_button_new_with_label ("2");
    przycisk[10] = gtk_button_new_with_label ("3");
    przycisk[11] = gtk_button_new_with_label ("-");

    przycisk[12] = gtk_button_new_with_label ("0");
    przycisk[13] = gtk_button_new_with_label (",");
    przycisk[14] = gtk_button_new_with_label ("=");
    przycisk[15] = gtk_button_new_with_label ("+");

    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            gtk_grid_attach(GTK_GRID(tabela), przycisk[(y*4)+x], x, y, 1, 1);
            /* dodaje widżety do kontenera, argumety: kontener, widżet, gdzie ma być wysokość, szerokość,
             * długość i wysokość widżetu, jak źle napiszesz to będą nachodzić na siebie    */
       //   gtk_table_attach_defaults (GTK_TABLE(tabela), przycisk[(y*4)+x], x, x+1, y, y+1); tak było w starym tutorialu

    gtk_container_add(GTK_CONTAINER(okno), tabela);

    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(okno);

    gtk_main();

    return 0;
}
