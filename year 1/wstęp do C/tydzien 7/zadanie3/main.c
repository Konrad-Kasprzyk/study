#include <stdio.h>
#include <stdlib.h>

int licznik=0;

void zrob(int wiersz,int kolumna,char tab[][100])
{
 tab[wiersz][kolumna]='&';


    if (wiersz>0)
        if (tab[wiersz-1][kolumna]=='-')  tab[wiersz-1][kolumna]='%';

    if (wiersz<999)
        if (tab[wiersz+1][kolumna]=='-')  tab[wiersz+1][kolumna]='%';

     if (kolumna>0)
        if (tab[wiersz][kolumna-1]=='-')  tab[wiersz][kolumna-1]='%';

         if (kolumna<99)
        if (tab[wiersz][kolumna+1]=='-')  tab[wiersz][kolumna+1]='%';



}

void zamien(char tab[][100])
{
    int i,j;
    for (i=0;i<1000;i++)
        for (j=0;j<100;j++)
            if (tab[i][j]=='%') tab[i][j]='!';



}

int sprawdz(char tab[][100])
{
    int i,j;
    for (i=0;i<1000;i++)
        for (j=0;j<100;j++)
            if (tab[i][j]=='-')  return 1;

            return 0;
}

int main()
{
    int wiersz,kolumna,spraw=0,i,j;
    scanf("%d",&wiersz);
    scanf("%d",&kolumna);
    char tab[1000][100];
printf("%d\n",wiersz);
printf("%d\n",kolumna);

    for (i=0;i<1000;i++)
        for (j=0;j<100;j++)
            tab[i][j]='0';

    for (i=0;i<wiersz;i++)
        for (j=0;j<kolumna;j++)
        {
        scanf("%c",&tab[i][j]);
        if (tab[i][j]=='\n')  scanf("%c",&tab[i][j]);
        }

   /*     for (i=0;i<wiersz;i++)
        {
        for (j=0;j<kolumna;j++)
            printf("%c ",tab[i][j]);

            printf("\n");
            }
*/
        skok:
        spraw=0;
     for (i=0;i<wiersz;i++)
     {
        for (j=0;j<kolumna;j++)
            if(tab[i][j]=='!')
                {
                    zrob(i,j,tab);
                    spraw=1;
                    //printf("tu jestem tab[%d][%d]\n",i,j);
                }
    }
    if (spraw==1) {  zamien(tab); licznik++; goto skok; }
    if (sprawdz(tab)==1) printf("-1");
        else printf("%d",licznik-1);
    return 0;
}
