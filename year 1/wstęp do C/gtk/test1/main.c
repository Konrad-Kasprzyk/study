#include <gtk/gtk.h>

void wyswietl_polozenie(GtkWindow *okno, GdkEvent *zdarzenie)   // w tutorialu był jeszcze argument gpointer dane
{
   int x, y;
   char polozenie[10];

   x = zdarzenie->configure.x;      // w zdarzenie->configure znajdziemy położenie okna
   y = zdarzenie->configure.y;
   sprintf(polozenie, "%d, %d", x, y);  // przekazuje napis, czyli położenie okna

   gtk_window_set_title(okno, polozenie);   // ustawia taki tytuł okna jak ten napis, czyli bieżące położenie
}

int main (int argc, char *argv[]) {
    GtkWidget *okno;
    GtkWidget *kontener;
    GtkWidget *przycisk;

    gtk_init (&argc, &argv);

    okno = gtk_window_new (GTK_WINDOW_TOPLEVEL); // tworzy okno programu GTK_WINDOW określa domyślny rozmiar z dekoracjami
    gtk_window_set_default_size (GTK_WINDOW(okno), 300, 200); // ustala początkowy rozmiar okna, długość i wysokość
    gtk_window_set_position(GTK_WINDOW(okno), GTK_WIN_POS_CENTER);  // ustawia okno na środku ekranu
    gtk_window_set_title (GTK_WINDOW(okno), "Nasz program");        // ustawia tytuł programu
    gtk_container_set_border_width (GTK_CONTAINER(okno), 5);        /* określa grubość ramki między krawędzią kontenera,a
                                                                     * jego zawartością     */

    kontener = gtk_fixed_new();                         // tworzy kontener typu fixed
    gtk_container_add(GTK_CONTAINER(okno), kontener);   // umieszcza kontener w oknie programu


    przycisk = gtk_button_new_with_label("Twój pierwszy przycisk"); // tworzy przycisk z etykietą
    gtk_widget_set_size_request(przycisk, 180, 35);                 // ustawia rozmiar przycisku długość, wysokość
    gtk_fixed_put(GTK_FIXED(kontener), przycisk, 10, 10);           /* umieszcza go w kontenerze ustalając odległość
                                                                     * od lewej i od górnej krawędzi    */


    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    /* dodawanie akcji w przypadku jakiegoś zdarzenia,G_OBJECT(okno) to nazwa instancji gdzie podłaćżone ma być
     * zdarzenie, te zdarzenie to "destroy", G_CALLBACK(gtk_main_quit) to wykonywana funkcja odpowiedzialna za
     * zakończenie głównej pętli, a NULL to argumenty do niej   */


    g_signal_connect(G_OBJECT(okno), "configure-event", G_CALLBACK(wyswietl_polozenie), NULL);
    /* nazwa zdarzenia "configure-event" jest konieczna, argumenty do funkcji wysietl_polozenie same
     * zostaną przesłane    */

    gtk_widget_show_all(okno);

    gtk_main ();

    return 0;
}
