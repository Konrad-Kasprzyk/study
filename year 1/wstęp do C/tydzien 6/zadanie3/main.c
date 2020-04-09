#include <stdio.h>
#include <stdlib.h>

void zrob(int szerokosc,int wysokosc,int tab[][1000],int i,int j)
{
  tab[i][j]=2;
    if (i>0 && j>0)
        if (tab[i-1][j-1]==1) zrob(szerokosc,wysokosc,tab,i-1,j-1);

    if (i>0)
        if (tab[i-1][j]==1) zrob(szerokosc,wysokosc,tab,i-1,j);

    if (j>0)
        if (tab[i][j-1]==1) zrob(szerokosc,wysokosc,tab,i,j-1);

    if (i<wysokosc-1)
        if (tab[i+1][j]==1) zrob(szerokosc,wysokosc,tab,i+1,j);

    if (j<szerokosc-1)
       if (tab[i][j+1]==1)  zrob(szerokosc,wysokosc,tab,i,j+1);

    if (i>0 && j<szerokosc-1)
        if (tab[i-1][j+1]==1) zrob(szerokosc,wysokosc,tab,i-1,j+1);

    if (i<wysokosc-1 && j>0)
        if (tab[i+1][j-1]==1) zrob(szerokosc,wysokosc,tab,i+1,j-1);

    if (i<wysokosc-1 && j<szerokosc-1)
        if (tab[i+1][j+1]==1) zrob(szerokosc,wysokosc,tab,i+1,j+1);
}

void wyczysc(int tab[][1000])
{
    int i,j;
    for (i=0;i<1000;i++)
        for (j=0;j<1000;j++)
            if (tab[i][j]==2) tab[i][j]=0;
}

int main()
{
    int licznik=0;
    char napis[500];
    scanf("%s",napis);
    int wysokosc,szerokosc,i,j;
    scanf("%d",&szerokosc);
    scanf("%d",&wysokosc);
    int tab[1000][1000];

    for (i=0;i<1000;i++)
        for (j=0;j<1000;j++)
            tab[i][j]=0;

    for (i=0;i<wysokosc;i++)
        for (j=0;j<szerokosc;j++)
        {
        scanf("%d",&tab[i][j]);
        }
     for (i=0;i<wysokosc;i++)
        for (j=0;j<szerokosc;j++)
            if(tab[i][j]==1)
                {
                    licznik++;
                    zrob(szerokosc,wysokosc,tab,i,j);
                    wyczysc(tab);
                }
    printf("%d",licznik);
    return 0;
}
