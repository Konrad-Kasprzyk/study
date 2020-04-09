// Konrad Kasprzyk

#ifndef TESTY_H_INCLUDED
#define TESTY_H_INCLUDED

int partition(double tablica[], int p, int r);
void quicksort(double tablica[], int p, int r);
int compare (const void * a, const void * b);
double *generuj(int ile);
void kopiuj(double *tab,double *gdzie,int ile);
bool czy_poprawnie(double *tab,double *wynik,int ile);
void czas_sortowania(int ile);


#endif // TESTY_H_INCLUDED
