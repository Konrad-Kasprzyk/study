// Konrad Kasprzyk

#include <stdio.h>
// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include "kolejka.h"
#include <string.h>

void ClrScr(){
  printf("\033[2J"); // Czyści ekran
  printf("\033[0;0f"); // Ustawia kursor w lewym, górnym rogu
}

int main()
{

/*
struct listy{
char nazwa[30];
Kolejka adres;
};

*/
Listy_wsk wsk_list;
wsk_list=NULL;
char nazwa[30],ktora_lista[30]="Pierwsza lista";

int a,numer_listy=1,ile_list=1,b;
char x;
double liczba;
Kolejka wsk;



wsk_list=&lista_dodaj(&wsk_list,"Pierwsza lista");
wsk=wsk_list->adres;
printf("%s\n",wsk_list->nazwa);
wyswietl_listy(wsk_list,1);

/*
struct listy pierwszy;
strcpy(pierwszy.nazwa,"Pierwsza lista");
pierwszy.adres=wsk;
*/

while(true)
{
wsk=wybierz_liste(wsk_list,numer_listy);
printf("***Testowanie listy cyklicznej***\n");
printf("Jestes na liscie: %s\n",ktora_lista);
printf("10. Dodaj liste\n11. Wyswietl listy\n12. Zmien uzywana liste\n");
printf("1. Dodaj wartosc na poczatek listy\n2. Dodaj wartosc na koniec listy\n3. Wyswietl wartosc z poczatku listy\n");
printf("4. Wyswietl i usun wartosc z poczatku listy\n5. Sprawdz czy lista jest pusta\n6. Podaj dlugosc wskazanej listy\n");
printf("7. Koniec programu\n\nwybierz opcje: ");
scanf("%d",&a);
switch (a)
{
    case 10:
    printf("Podaj nazwe nowej listy: ");
    scanf("%s",nazwa);
    wsk_list=&lista_dodaj(&wsk_list,nazwa);
    ile_list++;
    break;

    case 11:
    wyswietl_listy(wsk_list,ile_list);
    break;

    case 12:
    wyswietl_listy(wsk_list,ile_list);
    printf("Podaj numer listy ktora chcesz uzywac: ");
    scanf("%d",&b);
    wsk=wybierz_liste(wsk_list,b);
    numer_listy=b;
    strcpy(ktora_lista,nazwa_listy(wsk_list,b));
    break;


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
