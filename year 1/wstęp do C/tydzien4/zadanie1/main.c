// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_CYFR 500

void wczytaj(char tab[]);
void na_tablice(const char tab[],int nowy[]);
void dodawanie(const int a[],const int b[], int wyn[]);
void odj( int tab[], int odj[],int wyn[], int d);
void odejmowanie(const int a[],const int b[], int wyn[]);
void mnozenie(const int a[],const int b[], int wyn2[]);
void wypisz(const int wyn[]);

int main()
{
    char x;
    char napis1[MAKS_CYFR];
    char napis2[MAKS_CYFR];
    int tab1[MAKS_CYFR];
    int tab2[MAKS_CYFR];
    int wynik[MAKS_CYFR];
    printf("Wpisz sama cyfre\n1. dodawanie\n2. odejmowanie\n3. mnozenie\n4. koniec programu\n");
    for(;;)
    {
        x=getchar();
        switch (x)
        {
            case '1':
            {
                printf("Podaj pierwsza liczbe: ");
                wczytaj(napis1);
                printf("Podaj druga liczbe: ");
                wczytaj(napis2);
                na_tablice(napis1,tab1);
                na_tablice(napis2,tab2);
                dodawanie(tab1,tab2,wynik);
                wypisz(wynik);
            }
            break;

            case '2':
            {
                printf("Podaj pierwsza liczbe: ");
                wczytaj(napis1);
                printf("Podaj druga liczbe: ");
                wczytaj(napis2);
                na_tablice(napis1,tab1);
                na_tablice(napis2,tab2);
                odejmowanie(tab1,tab2,wynik);
                wypisz(wynik);
            }
            break;
            case '3':
            {
                printf("Podaj pierwsza liczbe: ");
                wczytaj(napis1);
                printf("Podaj druga liczbe: ");
                wczytaj(napis2);
                na_tablice(napis1,tab1);
                na_tablice(napis2,tab2);
                mnozenie(tab1,tab2,wynik);
                wypisz(wynik);
            }
            break;
            case '4':
            {
                printf("Koniec programu\n");
                exit(0);
            }
            break;
            default:
                printf("zla liczba\n");
                break;
            getchar();

        }

        memset(tab1, 0, MAKS_CYFR * sizeof(int));
        memset(tab2, 0, MAKS_CYFR * sizeof(int));
        memset(wynik, 0, MAKS_CYFR * sizeof(int));
        memset(napis1, 0, MAKS_CYFR * sizeof(char));
        memset(napis2, 0, MAKS_CYFR * sizeof(char));

    }
    return 0;
}

void wczytaj(char tab[])
{
    int i=0;
    int c;
    c=getchar();
    while(c==' ' || c=='\t' || c=='\n')
        c=getchar();
    while(c>='0' && c<='9')
    {
        tab[i]=c;
        c=getchar();
        i++;
    }
    tab[i]='\0';
}

void na_tablice(const char tab[],int nowy[])
{
    int i,l;
    l=strlen(tab);
    nowy[0]=l;
    for(i=1; i<=l; i++)
    {
        nowy[i]=tab[i-1]-48;
    }
}
void dodawanie(const int a[],const int b[], int wyn[])
{
    int l,p,k;
    int tab[MAKS_CYFR];
    int dod[MAKS_CYFR];

    for (l=0;l<=a[0];l++)
    tab[l]=a[l];
    for (l=0;l<=b[0];l++)
    dod[l]=b[l];

    if (tab[0]>dod[0])
    {
        l=tab[0];
        p=dod[0];
    }
    else
    {
        l=dod[0];
        p=tab[0];
    }
    wyn[0]=l;
    if (tab[0]>=dod[0])
    {
        tab[0]=0;
        while(l>0)
        {
            if (p>0)
            {
                tab[l]=tab[l]+dod[p];
                k=tab[l]/10;
                tab[l]=tab[l]%10;
                tab[l-1]=tab[l-1]+k;
                l--;
                p--;
            }
            else
            {
                k=tab[l]/10;
                tab[l]=tab[l]%10;
                tab[l-1]=tab[l-1]+k;
                l--;
            }
        }
        if (tab[0]>0)
        {
            wyn[0]=wyn[0]+1;
            for (l=0; l<wyn[0]; l++)
                wyn[l+1]=tab[l];
        }
        else
        {
            for (l=1; l<=wyn[0]; l++)
            {
                wyn[l]=tab[l];
                 }
        }
    }

    else
    {
        dod[0]=0;
        while(l>0)
        {
            if (p>0)
            {
                dod[l]=dod[l]+tab[p];
                k=dod[l]/10;
                dod[l]=dod[l]%10;
                dod[l-1]=dod[l-1]+k;
                l--;
                p--;
            }
            else
            {
                k=dod[l]/10;
                dod[l]=dod[l]%10;
                dod[l-1]=dod[l-1]+k;
                l--;
            }
        }
        if (dod[0]>0)
        {
            wyn[0]=wyn[0]+1;
            for (l=0; l<wyn[0]; l++)
                wyn[l+1]=dod[l];
        }
        else
        {
            for (l=1; l<=wyn[0]; l++)
                wyn[l]=dod[l];
        }
    }
}
void odj( int tab[], int odj[],int wyn[], int d)
{
    int i,x=0;
    for (i=0;i<d;i++)
    {
        tab[i]=tab[i]-odj[i];
        if (tab[i]<0) {tab[i]+=10; tab[i+1]-=1;}
    }
    for (i=d-1;i>0;i--)
    {
        if (tab[i]==0)  x++;
        else            break;
    }

    wyn[0]=d-x;
    for (i=0;i<d-x;i++)
        wyn[i+1]=tab[d-x-i-1];
}

void odejmowanie(const int a[],const int b[], int wyn[])
{
    int i,p,x,dl_a,dl_b;
    dl_a=a[0];
    dl_b=b[0];
    int tab[MAKS_CYFR];
        memset(tab, 0, MAKS_CYFR * sizeof(int));
    int dod[MAKS_CYFR];
        memset(dod, 0, MAKS_CYFR * sizeof(int));

    for (i=0;i<dl_a;i++)
        tab[i]=a[i+1];

    for (i=0;i<dl_b;i++)
        dod[i]=b[i+1];

    x=dl_a-1;

    for (i=0;i<dl_a/2;i++)
    {
        p=tab[x];
        tab[x]=tab[i];
        tab[i]=p;
        x--;
    }
    x=dl_b-1;

    for (i=0;i<dl_b/2;i++)
    {
        p=dod[x];
        dod[x]=dod[i];
        dod[i]=p;
        x--;
    }

    if (dl_a>dl_b)
        odj(tab,dod,wyn,dl_a);
    if (dl_a<dl_b)
    {
        odj(dod,tab,wyn,dl_b);
        wyn[1]*=-1;
    }
    if (dl_a==dl_b)
    {
        for(i=1;i<=dl_a;i++)
        {
            if (a[i]>b[i])  { odj(tab,dod,wyn,dl_a); break; }
            if (a[i]<b[i])  { odj(dod,tab,wyn,dl_b); wyn[1]*=-1; break; }
            if (i==dl_a) { wyn[0]=1; wyn[1]=0; }
        }
    }
}
void mnozenie(const int a[],const int b[], int wyn2[])
{
    int wyn[MAKS_CYFR];
    int tab[MAKS_CYFR];
    int dod[MAKS_CYFR];
    int pom[MAKS_CYFR];
    int pom2[MAKS_CYFR];
    memset(wyn, 0, MAKS_CYFR * sizeof(int));
    memset(tab, 0, MAKS_CYFR * sizeof(int));
    memset(dod, 0, MAKS_CYFR * sizeof(int));
    memset(pom, 0, MAKS_CYFR * sizeof(int));
    memset(pom2, 0, MAKS_CYFR * sizeof(int));
    int dl_a=a[0];
    int i,l,p,k,x;
    int d=0,g=a[0];
    for (i=0;i<a[0];i++)
        tab[i]=a[i+1];

    for (i=0;i<b[0];i++)
        dod[i]=b[i+1];

    x=a[0]-1;
     for (i=0;i<dl_a/2;i++)
    {
        p=tab[x];
        tab[x]=tab[i];
        tab[i]=p;
        x--;
    }
       x=b[0]-1;
     for (i=0;i<b[0]/2;i++)
    {
        p=dod[x];
        dod[x]=dod[i];
        dod[i]=p;
        x--;
    }
    x=dl_a;

        for (i=0;i<a[0];i++)
        {
            pom[i]=tab[i]*dod[d];

        }
        for (i=0;i<a[0];i++)
            if (pom[i]>9)
            {
                k=pom[i]/10;
                pom[i]=pom[i]%10;
                pom[i+1]+=k;
            }
            if (pom[i]>0) g++;

    x=g-1;
     for (i=0;i<g/2;i++)
    {
        p=pom[x];
        pom[x]=pom[i];
        pom[i]=p;
        x--;
    }

        for (i=0;i<g;i++)
            pom[g-i]=pom[g-i-1];
        pom[0]=g;

    if (b[0]==1)
    {
        if (b[1]>0)
        for (i=0;i<=pom[0];i++)
            wyn2[i]=pom[i];
        else { wyn2[0]=1; wyn2[1]=0; }
        return ;
    }

    d+=1;

    for (l=0;l<b[0]-1;l++)
    {
        for (i=0;i<a[0]+d;i++)
        {
            pom2[i+d]=tab[i]*dod[d];
        }

        for (i=0;i<a[0]+d;i++)
            if (pom2[i]>9)
            {
                k=pom2[i]/10;
                pom2[i]=pom2[i]%10;
                pom2[i+1]+=k;
            }

            if (pom2[g]>0)  g++;

        for (i=0;i<d;i++)
            pom2[i]=0;

             x=g-1;
     for (i=0;i<g/2;i++)
    {
        p=pom2[x];
        pom2[x]=pom2[i];
        pom2[i]=p;
        x--;
    }
            for (i=0;i<g;i++)
                pom2[g-i]=pom2[g-i-1];
            pom2[0]=g;

        dodawanie(pom,pom2,wyn);

        for (i=0;i<=wyn[0];i++)
        pom[i]=wyn[i];

        for (i=0;i<g+2;i++)
            pom2[i]=0;

        d++;
    }

    for (i=0;i<=wyn[0];i++)
        wyn2[i]=wyn[i];
}
void wypisz (const int wyn[])
{
    int i;
    printf("wynik to: ");
    for (i=1;i<=wyn[0];i++)
        printf("%d",wyn[i]);
    printf("\n");
}
