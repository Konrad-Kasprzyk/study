// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void wczytaj(double tab[]);
void dodawanie(const double tab[],const double dod[], double wyn[]);
void odejmowanie(const double tab[],const double dod[], double wyn[]);
void iloczyn_skalarny(const double tab[],const double dod[], double wyn[]);
void mnozenie(const double tab[],const double p, double wyn[]);
void dlugosc(const double tab[], double wyn[]);
void wypisz1(const double wyn[]);
void wypisz3(const double wyn[]);

int main()
{
    double tab[3];
    double tab2[3];
    double wyn[3];
    double p;
    char x;
    x=getchar();
    for(;;)
    {
        switch (x)
        {
            case '+':
            {
                wczytaj(tab);
                wczytaj(tab2);
                dodawanie(tab,tab2,wyn);
                wypisz3(wyn);
            }
            break;

            case '-':
            {
                wczytaj(tab);
                wczytaj(tab2);
                odejmowanie(tab,tab2,wyn);
                wypisz3(wyn);
            }
            break;

            case '*':
            {
                wczytaj(tab);
                wczytaj(tab2);
                iloczyn_skalarny(tab,tab2,wyn);
                wypisz1(wyn);
            }
            break;

            case '.':
            {
                wczytaj(tab);
                scanf("%lf",&p);
                mnozenie(tab,p,wyn);
                wypisz3(wyn);
            }
            break;

            case '|':
            {
                wczytaj(tab);
                dlugosc(tab,wyn);
                wypisz1(wyn);
            }
            break;

        }
        x=getchar();
        if (x==' ' || x=='\t' || x=='\n') x=getchar();
        if (x==EOF) exit(0);
    }
    return 0;
}
void wczytaj(double tab[])
{
    scanf("%lf",&tab[0]);
    scanf("%lf",&tab[1]);
    scanf("%lf",&tab[2]);
}

void dodawanie(const double tab[],const double dod[], double wyn[])
{
    wyn[0]=dod[0]+tab[0];
    wyn[1]=dod[1]+tab[1];
    wyn[2]=dod[2]+tab[2];
}

void odejmowanie(const double tab[],const double dod[], double wyn[])
{
    wyn[0]=tab[0]-dod[0];
    wyn[1]=tab[1]-dod[1];
    wyn[2]=tab[2]-dod[2];
}

void iloczyn_skalarny(const double tab[],const double dod[], double wyn[])
{
    int i;
    double p;
    for (i=0;i<3;i++)
    {
        p=tab[i]*dod[i];
        wyn[0]+=p;
    }
}

void mnozenie(const double tab[],const double p, double wyn[])
{
    wyn[0]=tab[0]*p;
    wyn[1]=tab[1]*p;
    wyn[2]=tab[2]*p;
}

void dlugosc(const double tab[], double wyn[])
{
    double a;
    double b=0;
    int i;
    for (i=0;i<3;i++)
    {
        a=tab[i]*tab[i];
        b+=a;
    }
    wyn[0]=sqrt(b);
}

void wypisz1(const double wyn[])
{
    printf("%.2f\n",wyn[0]);
}

void wypisz3(const double wyn[])
{
    printf("%.2f ",wyn[0]);
    printf("%.2f ",wyn[1]);
    printf("%.2f\n",wyn[2]);
}
