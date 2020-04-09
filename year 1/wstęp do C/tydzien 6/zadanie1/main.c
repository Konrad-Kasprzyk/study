//Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "kolejka.h"

void ClrScr(){
  printf("\033[2J"); // Czyści ekran
  printf("\033[0;0f"); // Ustawia kursor w lewym, górnym rogu
}

int main()
{
    char x;
    double liczba;
    inicjalizacja();
    for(;;)
    {
    printf("***Testowanie kolejki***\n\n");
    printf("1. Dopisz do kolejki\n2. Wypisz z kolejki\n3. Oproznij kolejke\n4. Sprawdz czy jest pusta\n5. Wyjdz z programu\n");
    printf("\nWybierz opcje: ");
    scanf("%c",&x);
    if (x=='\n') scanf("%c",&x);
    switch (x)
    {
        case '1':
        printf("\nPodaj liczbe jaka chcesz dopisac: ");
        scanf("%lf",&liczba);
        dopisz(liczba);
        printf("\nnacisnij enter by kontynuować");
        x=getchar(); x=getchar();
        ClrScr();
        break;

        case '2':
        printf("\nWypisana liczba to: ");
        wypisz();
        printf("\nnacisnij enter by kontynuować");
        x=getchar(); x=getchar();
        ClrScr();
        break;

        case '3':
        printf("\nKolejka oprozniona");
        oproznij();
        printf("\nnacisnij enter by kontynuować");
        x=getchar(); x=getchar();
        ClrScr();
        break;

        case '4':
        if (czy_pusty()==false) printf("\nKolejka nie jest pusta");
        else printf("\nKolejka jest pusta");
        printf("\nnacisnij enter by kontynuować");
        x=getchar(); x=getchar();
        ClrScr();
        break;

        case '5':
        free(tablica);
        return 1;

        default:
        printf("\nNie ma takiej opcji w menu");
        printf("\nnacisnij enter by kontynuować");
        x=getchar(); x=getchar();
        ClrScr();
        break;
    }

    }
    return 0;
}
