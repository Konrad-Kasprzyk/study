// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include "kolejka.h"

void ClrScr(){
  printf("\033[2J"); // Czyści ekran
  printf("\033[0;0f"); // Ustawia kursor w lewym, górnym rogu
}

int main()
{
int a;
char x;
double liczba;
Kolejka wsk;
wsk=utworz();
while(true)
{
printf("***Testowanie listy cyklicznej***\n");
printf("1. Dodaj wartosc na poczatek listy\n2. Dodaj wartosc na koniec listy\n3. Wyswietl wartosc z poczatku listy\n");
printf("4. Wyswietl i usun wartosc z poczatku listy\n5. Sprawdz czy lista jest pusta\n6. Podaj dlugosc wskazanej listy\n");
printf("7. Koniec programu\n\nwybierz opcje: ");
scanf("%d",&a);
switch (a)
{
    case 1:
    printf("Podaj liczbe do dodania: ");
    scanf("%lf",&liczba);
    wsk=pocz_dodaj(wsk,liczba);
    break;

    case 2:
    printf("Podaj liczbe do dodania: ");
    scanf("%lf",&liczba);
    wsk=kon_dodaj(wsk,liczba);
    break;

    case 3:
    liczba=wyswietl_poczatek(wsk);
    printf("Liczba z poczatku listy to: %f",liczba);
    break;

    case 4:
    liczba=usun_i_wyswietl(&wsk);
    printf("Usunieta liczba z poczatku listy to: %f",liczba);
    break;

    case 5:
    if (czy_pusta(wsk)==true) printf("Lista jest pusta");
    else printf("Lista nie jest pusta");
    break;

    case 6:
    printf("Ilosc elementow listy: %d",dlugosc_listy(wsk));
    break;

    case 7:
    return 1;

    default:
    printf("Nie ma takiej opcji");
}
printf("\nNacisnij enter by kontynuowac");
x=getchar();
x=getchar();
printf("%c",x);       // bez tego mam -Werror
ClrScr();
}
    return 0;
}
