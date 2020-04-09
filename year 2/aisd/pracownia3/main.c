#include <stdio.h>
#include <stdlib.h>

int w,k;

long long int pot(char a){
    switch(a){
    case '0': return 1;
    case '1': return 7;
    case '2': return 49;
    case '3': return 343;
    case '4': return 2401;
    case '5': return 16807;
    case '6': return 117649;
    case '7': return 823543;
    case '8': return 5764801;
    case '9': return 40353607;
    default: return 40353607;
    }
}


long long int max(long long int a, long long int b){
if(a>b)
    return a;
else
    return b;
}


void gora(char tab[3][10005],long long int wyn[3][10005],int wiersz){
    // wiersz wskazuje dół naszej 3 wierszowej tablicy
    int znany_wiersz = wiersz%3;
    int liczony_wiersz = (wiersz-1)%3; // jeden wyżej
    long long int p;
    if(k==3){ // tylko 3 wiersze
        p=pot(tab[liczony_wiersz][0]); // wartość pola gdzie chcemy skoczyć
        if (wyn[znany_wiersz][2] == 0)
            wyn[liczony_wiersz][0]=0;
        else
            wyn[liczony_wiersz][0]=max(wyn[liczony_wiersz][0],p+wyn[znany_wiersz][2]); // albo tam skaczemy i dodajemy jego wartość, albo zostawiamy tamto pole tak jak było

        p=pot(tab[liczony_wiersz][2]);
        if (wyn[znany_wiersz][0] == 0)
            wyn[liczony_wiersz][2]=0;
        else
            wyn[liczony_wiersz][2]=max(wyn[liczony_wiersz][2],p+wyn[znany_wiersz][0]);
        return;
    }
    if(k==4){ // tylko 4 wiersze
        p=pot(tab[liczony_wiersz][0]); // wartość pola gdzie chcemy skoczyć
        if (wyn[znany_wiersz][2] == 0)
            wyn[liczony_wiersz][0]=0;
        else
            wyn[liczony_wiersz][0]=max(wyn[liczony_wiersz][0],p+wyn[znany_wiersz][2]); // albo tam skaczemy i dodajemy jego wartość, albo zostawiamy tamto pole tak jak było

        p=pot(tab[liczony_wiersz][1]);
        if (wyn[znany_wiersz][3] == 0)
            wyn[liczony_wiersz][1]=0;
        else
            wyn[liczony_wiersz][1]=max(wyn[liczony_wiersz][1],p+wyn[znany_wiersz][3]);

        p=pot(tab[liczony_wiersz][2]);
        if (wyn[znany_wiersz][0] == 0)
            wyn[liczony_wiersz][2]=0;
        else
            wyn[liczony_wiersz][2]=max(wyn[liczony_wiersz][2],p+wyn[znany_wiersz][0]);

        p=pot(tab[liczony_wiersz][3]);
        if (wyn[znany_wiersz][1] == 0)
            wyn[liczony_wiersz][3]=0;
        else
            wyn[liczony_wiersz][3]=max(wyn[liczony_wiersz][3],p+wyn[znany_wiersz][1]);
        return;
    }
    for (int i=0;i<k;i++){
        p=pot(tab[liczony_wiersz][i]);
        if(i<2) {
                if(wyn[znany_wiersz][i+2] == 0)
                    wyn[liczony_wiersz][i]=0;
                else
                    wyn[liczony_wiersz][i]=max(wyn[liczony_wiersz][i],p+wyn[znany_wiersz][i+2]);
        }
        else if (i>1 && i<k-2){
                if(wyn[znany_wiersz][i+2] == 0 && wyn[znany_wiersz][i-2] == 0)
                    wyn[liczony_wiersz][i]=0;
                else
                    wyn[liczony_wiersz][i]=max(wyn[liczony_wiersz][i],p+max(wyn[znany_wiersz][i-2],wyn[znany_wiersz][i+2]));
        }
        else {
                if(wyn[znany_wiersz][i-2] == 0)
                    wyn[liczony_wiersz][i]=0;
                else
                    wyn[liczony_wiersz][i]=max(wyn[liczony_wiersz][i],p+wyn[znany_wiersz][i-2]);
        }
    }
}

void dol(char tab[3][10005],long long int wyn[3][10005],int wiersz){
 // wiersz wskazuje dół naszej 3 wierszowej tablicy
    int znany_wiersz = (wiersz-2)%3;    // dwa wiersze wyżej
    int liczony_wiersz = wiersz%3;
    long long int p;

    for(int i=0;i<k;i++){
        p=pot(tab[liczony_wiersz][i]);
        if(i<1){
            if (wyn[znany_wiersz][i+1] == 0) // jeśli konik nie może skoczyć na jakieś pole to jest ono równe zero
                wyn[liczony_wiersz][i]=0;
            else
                wyn[liczony_wiersz][i]=p+wyn[znany_wiersz][i+1];
        }
        else if(i>k-2){
            if (wyn[znany_wiersz][i-1] == 0)
                wyn[liczony_wiersz][i]=0;
            else
                wyn[liczony_wiersz][i]=p+wyn[znany_wiersz][i-1];
        }
        else {
                if (wyn[znany_wiersz][i-1] == 0 && wyn[znany_wiersz][i+1] == 0)
                    wyn[liczony_wiersz][i]=0;
                else
                    wyn[liczony_wiersz][i]=p+max(wyn[znany_wiersz][i+1],wyn[znany_wiersz][i-1]);
        }
    }
}

long long int maks(long long int wyn[3][10005],int wiersz){
    long long int m=wyn[wiersz][0];

    for(int i=1; i<k; i++){
        if(m<wyn[wiersz][i])
            m=wyn[wiersz][i];
    }

    return m;
}

int main()
{
    scanf("%d",&w);
    scanf("%d",&k);
    long long int wyn[3][10005];
    char tab[3][10005];

    scanf("%s",tab[0]);
    scanf("%s",tab[1]);
    scanf("%s",tab[2]);

    for(int i=0; i<k; i++){
        wyn[0][i] = pot(tab[0][i]);
        wyn[1][i] = 0;
        wyn[2][i] = 0;
	}

    for(int i=2; i<w-1; i++){
        dol(tab,wyn,i);
        gora(tab,wyn,i);
        scanf("%s",tab[ (i+1)%3 ]); // wczytaj linikę niżej wartośi. Aby się ograniczyć do 3 wierszy pamięciowo to mod3
	}

	dol(tab,wyn,w-1); // gdy i = w-1 to wychodzi z pętli, bo wczytaliśmy już wszystkie wiersze, a został jeszcze ten ostatni w-1 wiersz do obliczenia w wyn

    printf("%lld",maks(wyn,(w-1)%3));

    return 0;
}
