#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct punkt{
    int x;
    int y;
    int pozycjaX;
};

struct para_punktow{
    struct punkt p1;
    struct punkt p2;
};

long long int dist(struct punkt p1,struct punkt p2){
    long long int l=(long long int)(p1.x-p2.x);
    l *= l;
    long long int p=(long long int)(p1.y-p2.y);
    p *= p;
    return l+p;
}

    int n;
    struct punkt X[1000000];
    struct punkt Y[1000000];
    struct punkt pom_tabL[1000000];
    struct punkt pom_tabP[1000000];


int partitionX(struct punkt tablica[], int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
    int x = tablica[(p+r)/2].x; // obieramy x
    int i = p, j = r; // i, j - indeksy w tabeli
    struct punkt w;
    while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
    {
        while (tablica[j].x > x) // dopoki elementy sa wieksze od x
            j--;
        while (tablica[i].x < x) // dopoki elementy sa mniejsze od x
            i++;
        if (i < j) // zamieniamy miejscami gdy i < j
        {
            w = tablica[i];
            tablica[i] = tablica[j];
            tablica[j] = w;
            i++;
            j--;
        }
        else // gdy i >= j zwracamy j jako punkt podzialu tablicy
            return j;
    }
}

void quicksortX(struct punkt tablica[], int p, int r) // sortowanie szybkie
{
    int q;
    if (p < r)
    {
        q = partitionX(tablica,p,r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
        quicksortX(tablica, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
        quicksortX(tablica, q+1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
    }
}


int partitionY(struct punkt tablica[], int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
    int y = tablica[(p+r)/2].y; // obieramy y
    int i = p, j = r; // i, j - indeksy w tabeli
    struct punkt w;
    while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
    {
        while (tablica[j].y > y) // dopoki elementy sa wieksze od x
            j--;
        while (tablica[i].y < y) // dopoki elementy sa mniejsze od x
            i++;
        if (i < j) // zamieniamy miejscami gdy i < j
        {
            w = tablica[i];
            tablica[i] = tablica[j];
            tablica[j] = w;
            i++;
            j--;
        }
        else // gdy i >= j zwracamy j jako punkt podzialu tablicy
            return j;
    }
}

void quicksortY(struct punkt tablica[], int p, int r) // sortowanie szybkie
{
    int q;
    if (p < r)
    {
        q = partitionY(tablica,p,r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
        quicksortY(tablica, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
        quicksortY(tablica, q+1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
    }
}

struct para_punktow smallest_dist(int L,int P){        //indeksy w tablicy X
    long long int min_dist = dist(X[L],X[P]);
    struct para_punktow min_pair;
    min_pair.p1 = X[L];
    min_pair.p2 = X[P];
    long long int pom_dist,pom_dist2;

    if(X[L].x == X[P].x){                                       // Wszystkie punkty są na jednej osi x
            struct punkt previous_point = X[L];
            int i=0, k=0;                                       // k = ile liczb już sprawdziliśmy
        while(k<P-L+1){                                          /*sprawdzamy w tablicy Y jakie są odległości między punktami na tej
                                                                samej prostej x. Wykonamy tyle razy ile jest punktów*/
            if (L <= Y[i].pozycjaX && Y[i].pozycjaX <= P){
                if(k==0){                                       // pierwszy punkt już mamy
                    k++;
                    continue;
                }
                pom_dist = dist(previous_point,Y[i]);
                if (min_dist < pom_dist){                       // znaleźliśmy mniej odległe punkty
                    min_dist = pom_dist;
                    min_pair.p1 = previous_point;
                    min_pair.p2 = Y[i];
                }
                previous_point = Y[i];
                k++;
            }
            i++;
        }
       return min_pair;
    }

    if(P-L<1000){      // Wszystkich punktów z tego przedziału jest mniej niż 1000
        for (int i=L;i<=P;i++)
            for (int j=L;j<=P;j++){
                if (i==j) continue;
                pom_dist = dist(X[i],X[j]);      // sprawdzamy czy para punktów jest mniej odległa
                if (min_dist > pom_dist){
                    min_dist = pom_dist;
                    min_pair.p1 = X[i];
                    min_pair.p2 = X[j];
                }
            }
        return min_pair;
    }

    int l=(P+L)/2;                                      // indeks punktu którego x jest podziałem
    struct para_punktow PP1 = smallest_dist(L,l);
    struct para_punktow PP2 = smallest_dist(l+1,P);


    pom_dist = dist(PP1.p1,PP1.p2);
    pom_dist2 = dist(PP2.p1,PP2.p2);
    if (pom_dist < pom_dist2){
        min_pair = PP1;
        min_dist = pom_dist;
    }
    else{
        min_pair = PP2;
        min_dist = pom_dist2;
    }


    int d = (int)floor(sqrt((double)min_dist));  // maksymalna odległość na jaką mogą być odlegle punkty od osi podziału x
    int os_podzialu = X[l].x;
    int l_min = os_podzialu - d;
    int l_max = os_podzialu + d;

    int n_pomL=0; // ile mamy punktów w tablicy pomocniczej trzyamjącej punkty na lewo od osi podziału x
    int n_pomP=0; // ile mamy punktów w tablicy pomocniczej trzyamjącej punkty na prawo od osi podziału x


    for (int i=0;i<n;i++){          // tworzymy tablice punktów odległych od l mniej niż min_dist posortowanych po y, oddzielnie dla lewej i prawej strony od osi
        if (Y[i].x < l_min || l_max < Y[i].x)
            continue;

        if (Y[i].x < os_podzialu){
            pom_tabL[n_pomL] = Y[i];
            n_pomL++;
        }else
        {
            pom_tabP[n_pomP] = Y[i];
            n_pomP++;
        }
    }


    // wykonamy porównania iterując po mniejszym zbiorze
    if(n_pomL < n_pomP){
        int ile_sprawdziles = 0;
        int j=0;
        for (int i=0; i<n_pomL; i++){
            while(true){
                if (j>=n_pomP) break;                   // nie ma więcej w durgiej tablicy niesprawdzonych punktów

                if(pom_tabP[j].y < pom_tabL[i].y){
                    if(pom_tabP[j].y + d <= pom_tabL[i].y){         // roznica miedzy y jest zbyt duża by liczyć czy te punkty są najmniej odległe od siebie
                        j++;
                        continue;
                    }
                    pom_dist = dist(pom_tabP[j],pom_tabL[i]);       // sprawdzenie czy dana para punktów jest najmniej odległa
                    if (pom_dist < min_dist){
                        min_dist = pom_dist;
                        min_pair.p1 = pom_tabP[j];
                        min_pair.p2 = pom_tabL[i];
                    }
                    ile_sprawdziles++;
                    j++;
                }else{
                    if(pom_tabL[i].y + d <= pom_tabP[j].y){         // roznica miedzy y jest zbyt duża by liczyć czy te punkty są najmniej odległe od siebie
                        j-=ile_sprawdziles;
                        ile_sprawdziles=0;
                        break;                                      // wyjście z pętli bo następne punkty na pewno są za daleko
                    }
                    pom_dist = dist(pom_tabP[j],pom_tabL[i]);       // sprawdzenie czy dana para punktów jest najmniej odległa
                    if (pom_dist < min_dist){
                        min_dist = pom_dist;
                        min_pair.p1 = pom_tabP[j];
                        min_pair.p2 = pom_tabL[i];
                    }
                    ile_sprawdziles++;
                    j++;
                }
            }
        }
    }else{
        int ile_sprawdziles = 0;
        int j=0;
        for (int i=0; i<n_pomP; i++){
            while(true){
                if (j>=n_pomL) break;                   // nie ma więcej w durgiej tablicy niesprawdzonych punktów

                if(pom_tabL[j].y < pom_tabP[i].y){
                    if(pom_tabL[j].y + d <= pom_tabP[i].y){         // roznica miedzy y jest zbyt duża by liczyć czy te punkty są najmniej odległe od siebie
                        j++;
                        continue;
                    }
                    pom_dist = dist(pom_tabL[j],pom_tabP[i]);       // sprawdzenie czy dana para punktów jest najmniej odległa
                    if (pom_dist < min_dist){
                        min_dist = pom_dist;
                        min_pair.p1 = pom_tabL[j];
                        min_pair.p2 = pom_tabP[i];
                    }
                    ile_sprawdziles++;
                    j++;
                }else{
                    if(pom_tabP[i].y + d <= pom_tabL[j].y){         // roznica miedzy y jest zbyt duża by liczyć czy te punkty są najmniej odległe od siebie
                        j-=ile_sprawdziles;
                        ile_sprawdziles=0;
                        break;                                      // wyjście z pętli bo następne punkty na pewno są za daleko
                    }
                    pom_dist = dist(pom_tabL[j],pom_tabP[i]);       // sprawdzenie czy dana para punktów jest najmniej odległa
                    if (pom_dist < min_dist){
                        min_dist = pom_dist;
                        min_pair.p1 = pom_tabL[j];
                        min_pair.p2 = pom_tabP[i];
                    }
                    ile_sprawdziles++;
                    j++;
                }
            }
        }
    }

    return min_pair;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++)
        scanf("%d %d",&X[i].x,&X[i].y);

    quicksortX(X,0,n-1);

    for (int i=0;i<n;i++){
        X[i].pozycjaX=i;
        Y[i]=X[i];
    }

    quicksortY(Y,0,n-1);

    struct para_punktow wynik = smallest_dist(0,n-1);

    printf("%d %d\n",wynik.p1.x,wynik.p1.y);
    printf("%d %d",wynik.p2.x,wynik.p2.y);

    return 0;
}
