// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sortuj(int tab[],int s,int n)
{
    int i,j,p;
    for (i=s; i<n; i++)
        for (j=s; j<n-1; j++)
            if (tab[j]>tab[j+1])
            {
                p=tab[j];
                tab[j]=tab[j+1];
                tab[j+1]=p;
            }
}

void wypisz(int tab[], int n)
{
    int i;
    for (i=0; i<n; i++)
        printf("%d",tab[i]);
    printf("\n");

}

bool spr(int tab[],int s,int n)   // 1 gdy wszystkie elementy od s do n są malejąco
{
    if (s==n-1) return 1;
    int i;
    for (i=s; i<n-1; i++)
    {
        if (tab[i]<tab[i+1]) return 0;
    }
    return 1;
}

void zamien(int tab[],int x, int n) // zamienia kolejną od x liczbę na najmniej większą
{
    int i,min,p,p_2,l;
    for (i=x; i<n; i++)
    {
        if ((tab[x]-tab[i+1])<0)
        {
            min=tab[x]-tab[i+1];
            break;
        }
    }
    for (i=x; i<n; i++)
    {
        if ((tab[x]-tab[i+1])<0)
        {
            p=tab[x]-tab[i+1];
            if (p>=min)
            {
                min=p;
                l=i+1;
            }
        }
    }
    p_2=tab[x];
    tab[x]=tab[l];
    tab[l]=p_2;
}


bool permutacja(int tab[],int s,int n)
{
skok:
    if (n-1==s)  return 1;
    if (permutacja(tab,s+1,n)==1)
    {
        if (spr(tab,s,n)==0)
        {
            zamien(tab,s,n);
            sortuj(tab,s+1,n);
            wypisz(tab,n);
            goto skok;
        }
        else return 1;
    }
    return 1;       //  Nie wiem czemu muszę tu dać return 1, skoro funkcja tam nie dochodzi
                    //  Bez tego mam błąd -Werror
}

int main()
{
    int n,i;
    scanf("%d",&n);
    int tab[n];
    for (i=0; i<n; i++)
        tab[i]=i+1;
    if (n==0)
    {
        printf("0");
        return 1;
    }

    wypisz(tab,n);

    if (permutacja(tab,0,n)==1) return 2;

    return 0;
}
