#include <gtk/gtk.h>

void toggle_title(GtkWidget *widget)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
        gtk_button_set_label(GTK_BUTTON(widget), "Wciśnięto!");
    else
        gtk_button_set_label(GTK_BUTTON(widget), "Nie wciśnięto!");
}

int main( int argc, char *argv[])
{
    GtkWidget *okno;
    GtkWidget *vbox;

    GtkWidget *znaczek;
    GtkWidget *toggleButton;

    gtk_init(&argc, &argv);

    okno = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW(okno), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size (GTK_WINDOW(okno), 150, 75);
    gtk_window_set_title (GTK_WINDOW(okno), "Kurs GTK+");
    gtk_container_set_border_width (GTK_CONTAINER(okno), 5);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_container_add(GTK_CONTAINER(okno), vbox);

    znaczek = gtk_check_button_new_with_label ("Nie wciśnięto!");
    toggleButton = gtk_toggle_button_new_with_label ("Nie wciśnięto!");

    gtk_box_pack_start (GTK_BOX(vbox), znaczek, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), toggleButton, TRUE, TRUE, 0);

    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(znaczek, "clicked", G_CALLBACK(toggle_title), NULL);
    g_signal_connect(toggleButton, "clicked", G_CALLBACK(toggle_title), NULL);

    gtk_widget_show_all(okno);

    gtk_main();

    return 0;
}
