#include <stdio.h>
#include <stdlib.h>

struct elem{
    unsigned long long int iloczyn;
    unsigned int x;
    unsigned int y;
};

    int ile_elem = 0;

// działa dla k>0 w tablicy w kopcu elementy są od 1 a nie od zera
void przesun_nizej(struct elem tab[], int k){
    int j;
    struct elem pom;
    do{
        j=k;
        if (2*j<=ile_elem && tab[2*j].iloczyn>tab[k].iloczyn)
            k=2*j;
        if (2*j<ile_elem && tab[2*j + 1].iloczyn>tab[k].iloczyn)
            k=2*j + 1;
        pom=tab[j];
        tab[j]=tab[k];
        tab[k]=pom;
    }while(j!=k);
}

void przesun_wyzej(struct elem tab[], int k){
    int j;
    struct elem pom;
    do{
        j=k;
        if (j>1 && tab[j/2].iloczyn<tab[k].iloczyn)
            k=j/2;
        pom=tab[j];
        tab[j]=tab[k];
        tab[k]=pom;
    }while(j!=k);
}

void wstaw_do_tablicy(struct elem tab[],unsigned int x,unsigned int y){
    ile_elem++;
    tab[ile_elem].x=x;
    tab[ile_elem].y=y;
    tab[ile_elem].iloczyn=(unsigned long long) x*y;
    przesun_wyzej(tab,ile_elem);
}

struct elem wez_najwiekszy_numer(struct elem tab[]){
    struct elem zwroc;
    zwroc=tab[1];
    tab[1]=tab[ile_elem];
    ile_elem--;
    przesun_nizej(tab,1);
    return zwroc;
};


int main()
{
    struct elem tab[100000];
    struct elem pom[5000]; // tutaj będą elementy o tych samych iloczynach ale różnych x,y
    struct elem naj, naj2;
    int wypisane = 2;
    int M, k, p; // p oznacza ile elementów już mamy o tych samych iloczynach ale różnych x,y
    unsigned long long int wynik;
    scanf("%d",&M);
    scanf("%d",&k);
    if(k==1){
            wynik=(unsigned long long) M*M;
            printf("%llu\n",wynik);
        return 0;
    }
     if(k==2){
            wynik=(unsigned long long) M*M;
            printf("%llu\n",wynik);
            if(M>1){
                wynik=(unsigned long long) M*(M-1);
            printf("%llu\n",wynik);
            }
        return 0;
    }
    if(M<3){
        printf("4\n2\n1\n");
        return 0;
    }

    wynik=(unsigned long long) M*M;
            printf("%llu\n",wynik);
    wynik=(unsigned long long) M*(M-1);
            printf("%llu\n",wynik);
    wstaw_do_tablicy(tab,M-1,M-1);
    wstaw_do_tablicy(tab,M-2,M);

int test = 1; // jeśli test = 1 to mamy dany iloczyn gdzie x,y są różne od x,y z wcześniejszych elementów z tym samym iloczynem
naj =  wez_najwiekszy_numer(tab);
     while(wypisane<k){

            if (ile_elem >= 1){
                p=1;
                pom[0]=naj;     // z tablicy pom dodajemy do kopca elementy, wiemy że w niej są elementy o tym samym iloczynie ale różnych x,y
                naj2 =  wez_najwiekszy_numer(tab);
                while (naj.iloczyn == naj2.iloczyn){ // dopóki mamy elementy o tym samym iloczynie
                    test=1;
                    for(int i=0; i<p; i++){
                        if (pom[i].x == naj2.x && pom[i].y == naj2.y)
                        {
                            test=0;             // jeżeli mamy już ustalone z jakich x,y dodać elementy to unikamy duplikatu
                            break;
                        }
                    }
                    if(test==1) //ten sam iloczyn ale inne x,y
                    {
                        pom[p].x=naj2.x;
                        pom[p].y=naj2.y;
                        p++;
                    }
                    if(ile_elem < 1)
                        break;

                    naj2=wez_najwiekszy_numer(tab);
                }

                for(int i=0; i<p; i++){     // z tablicy pom wstawiamy elementy do kopca, nie ma w nim elementów o tym samym x,y
                    if(pom[i].x <= pom[i].y-1)              // patrzymy tylko na liczby na prawo od głównej przekątnej
                        wstaw_do_tablicy(tab,pom[i].x,pom[i].y-1);
                    if(pom[i].x > 1)                               // czy nie wychodzi poza górną granicę tabliczki mnożenia
                        wstaw_do_tablicy(tab,pom[i].x-1,pom[i].y);
                    }


                printf("%llu\n",naj.iloczyn);
                wypisane++;
                if (ile_elem == 0)
                    return 0;

                if (naj.iloczyn == naj2.iloczyn)        // to się zdaży jak mamy dwa elementy o tym samym iloczynie, wtedy z wewnętrznego whiles
                    naj=wez_najwiekszy_numer(tab);      // liczby to bierzemy z dodanych przed chwilą liczb największą
                else
                    naj=naj2;
            }else{

                if(naj.x <= naj.y-1)              // patrzymy tylko na liczby na prawo od głównej przekątnej
                    wstaw_do_tablicy(tab,naj.x,naj.y-1);

                if(naj.x > 1)                               // czy nie wychodzi poza górną granicę tabliczki mnożenia
                    wstaw_do_tablicy(tab,naj.x-1,naj.y);

                printf("%llu\n",naj.iloczyn);
                wypisane++;
                if (ile_elem == 0)
                    return 0;

                naj=wez_najwiekszy_numer(tab);
            }
    }
    return 0;
}
