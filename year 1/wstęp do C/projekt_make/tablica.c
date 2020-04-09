//Konrad Kasprzyk

#include "tablica.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char kogo_ruch='c';
int biale=2;
int czarne=2;

void inicjuj()
{
kogo_ruch='c';

int i,j;
for (i=0;i<10;i++)
    for (j=0;j<10;j++)
        tab[i][j]='p';

tab[4][4]='b';
tab[4][5]='c';
tab[5][4]='c';
tab[5][5]='b';
}

void tab_string(char *str)
{
    int a=1,b=1,i;

    str[0]=kogo_ruch;
    for (i=1;i<=64;i++)
        {
            str[i]=tab[a][b];
            b++;
            if (b==9) { a++; b=1; }
        }
    a=czarne/10;
    b=czarne%10;
    str[65]=a+48;
    str[66]=b+48;
    a=biale/10;
    b=biale%10;
    str[67]=a+48;
    str[68]=b+48;
    str[69]='\0';
}

void string_tab(char *str)
{
    kogo_ruch=str[0];

    int a=1,b=1,i;
    for (i=1;i<=64;i++)
        {
            tab[a][b]=str[i];
            b++;
            if (b==9) { a++; b=1; }
        }
    a=str[65]-48;
    b=str[66]-48;
    czarne=(a*10)+b;
    a=str[67]-48;
    b=str[68]-48;
    biale=(a*10)+b;

}

void zamien_poziom(int polozenie,bool czy_prawo)
{
    int x,y;
    y=polozenie%10;
    x=polozenie/10;
    char przeciwny_kolor;
    if (kogo_ruch=='c') przeciwny_kolor='b';
    else przeciwny_kolor='c';

    if (czy_prawo>0)
    {
        while(tab[x][y+1]==przeciwny_kolor)
        {
            tab[x][y+1]=kogo_ruch;
            if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            y++;
        }
    }
    else
    {
        while(tab[x][y-1]==przeciwny_kolor)
        {
            tab[x][y-1]=kogo_ruch;
             if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            y--;
        }
    }
}

bool znajdz_poziom(int polozenie,bool czy_prawo)
{
int x,y;
y=polozenie%10;
x=polozenie/10;
char przeciwny_kolor;
if (kogo_ruch=='c') przeciwny_kolor='b';
else przeciwny_kolor='c';

    if (czy_prawo>0)
    {
        if (tab[x][y+1]==kogo_ruch || tab[x][y+1]=='p') return 0;
        while(tab[x][y+1]==przeciwny_kolor)
        {
            y++;
        }
        if (tab[x][y+1]=='p') return 0;
        else return 1;
        //else return (x*10)+y+1;
    }
    else
    {
        if (tab[x][y-1]==kogo_ruch || tab[x][y-1]=='p') return 0;
        while(tab[x][y-1]==przeciwny_kolor)
        {
            y--;
        }
        if (tab[x][y-1]=='p') return 0;
        else return 1;
    }
}

void zamien_pion(int polozenie,bool czy_gora)
{
int x,y;
y=polozenie%10;
x=polozenie/10;
char przeciwny_kolor;
if (kogo_ruch=='c') przeciwny_kolor='b';
else przeciwny_kolor='c';

    if (czy_gora>0)
    {
        while(tab[x-1][y]==przeciwny_kolor)
        {
            tab[x-1][y]=kogo_ruch;
             if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            x--;
        }
    }
    else
    {
        while(tab[x+1][y]==przeciwny_kolor)
        {
            tab[x+1][y]=kogo_ruch;
             if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            x++;
        }
    }
}

bool znajdz_pion(int polozenie,bool czy_gora)
{
int x,y;
y=polozenie%10;
x=polozenie/10;
char przeciwny_kolor;
if (kogo_ruch=='c') przeciwny_kolor='b';
else przeciwny_kolor='c';

    if (czy_gora>0)
    {
        if (tab[x-1][y]==kogo_ruch || tab[x-1][y]=='p') return 0;
        while(tab[x-1][y]==przeciwny_kolor)
        {
            x--;
        }
        if (tab[x-1][y]=='p') return 0;
        else return 1;
    }
    else
    {
        if (tab[x+1][y]==kogo_ruch || tab[x+1][y]=='p') return 0;
        while(tab[x+1][y]==przeciwny_kolor)
        {
            x++;
        }
        if (tab[x+1][y]=='p') return 0;
        else return 1;
    }
}

void zamien_ukos(int polozenie,bool czy_gora,bool czy_prawo)
{
int x,y;
y=polozenie%10;
x=polozenie/10;
char przeciwny_kolor;
if (kogo_ruch=='c') przeciwny_kolor='b';
else przeciwny_kolor='c';

    if (czy_gora>0 && czy_prawo>0)
    {
        while(tab[x-1][y+1]==przeciwny_kolor)
        {
            tab[x-1][y+1]=kogo_ruch;
             if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            x--;
            y++;
        }
    }
    if (czy_gora>0 && czy_prawo<1)
    {
        while(tab[x-1][y-1]==przeciwny_kolor)
        {
            tab[x-1][y-1]=kogo_ruch;
             if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            x--;
            y--;
        }
    }
    if (czy_gora<1 && czy_prawo>0)
    {
        while(tab[x+1][y+1]==przeciwny_kolor)
        {
            tab[x+1][y+1]=kogo_ruch;
             if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            x++;
            y++;
        }
    }
    if (czy_gora<1 && czy_prawo<1)
    {
        while(tab[x+1][y-1]==przeciwny_kolor)
        {
            tab[x+1][y-1]=kogo_ruch;
             if (kogo_ruch=='c') { czarne++; biale--; }
            else { biale++; czarne--; }
            x++;
            y--;
        }
    }
}

bool znajdz_ukos(int polozenie,bool czy_gora,bool czy_prawo)
{
int x,y;
y=polozenie%10;
x=polozenie/10;
char przeciwny_kolor;
if (kogo_ruch=='c') przeciwny_kolor='b';
else przeciwny_kolor='c';

    if (czy_gora>0 && czy_prawo>0)
    {
        if (tab[x-1][y+1]==kogo_ruch || tab[x-1][y+1]=='p') return 0;
        while(tab[x-1][y+1]==przeciwny_kolor)
        {
            x--;
            y++;
        }
        if (tab[x-1][y+1]=='p') return 0;
        else return 1;
    }
    if (czy_gora>0 && czy_prawo<1)
    {
        if (tab[x-1][y-1]==kogo_ruch || tab[x-1][y-1]=='p') return 0;
        while(tab[x-1][y-1]==przeciwny_kolor)
        {
            x--;
            y--;
        }
        if (tab[x-1][y-1]=='p') return 0;
        else return 1;
    }
    if (czy_gora<1 && czy_prawo>0)
    {
        if (tab[x+1][y+1]==kogo_ruch || tab[x+1][y+1]=='p') return 0;
        while(tab[x+1][y+1]==przeciwny_kolor)
        {
            x++;
            y++;
        }
        if (tab[x+1][y+1]=='p') return 0;
        else return 1;
    }
    if (czy_gora<1 && czy_prawo<1)
    {
        if (tab[x+1][y-1]==kogo_ruch || tab[x+1][y-1]=='p') return 0;
        while(tab[x+1][y-1]==przeciwny_kolor)
        {
            x++;
            y--;
        }
        if (tab[x+1][y-1]=='p') return 0;
        else return 1;
    }
    return 0;
}

void wykonaj_ruch(int polozenie)
{
    int x,y;
    y=polozenie%10;
    x=polozenie/10;

    if (znajdz_pion(polozenie,1)==1)        zamien_pion(polozenie,1);
    if (znajdz_pion(polozenie,0)==1)        zamien_pion(polozenie,0);
    if (znajdz_poziom(polozenie,1)==1)      zamien_poziom(polozenie,1);
    if (znajdz_poziom(polozenie,0)==1)      zamien_poziom(polozenie,0);
    if (znajdz_ukos(polozenie,1,1)==1)      zamien_ukos(polozenie,1,1);
    if (znajdz_ukos(polozenie,1,0)==1)      zamien_ukos(polozenie,1,0);
    if (znajdz_ukos(polozenie,0,1)==1)      zamien_ukos(polozenie,0,1);
    if (znajdz_ukos(polozenie,0,0)==1)      zamien_ukos(polozenie,0,0);

    tab[x][y]=kogo_ruch;

    if (kogo_ruch=='c') czarne++;
    else biale++;

}

int sprawdz_ruch(int polozenie)
{
    int x,y;
    y=polozenie%10;
    x=polozenie/10;
    if (tab[x][y]!='p') return 0;

    if (znajdz_pion(polozenie,1)==1)    { wykonaj_ruch(polozenie); return 1; }
    if (znajdz_pion(polozenie,0)==1)    { wykonaj_ruch(polozenie); return 1; }
    if (znajdz_poziom(polozenie,1)==1)  { wykonaj_ruch(polozenie); return 1; }
    if (znajdz_poziom(polozenie,0)==1)  { wykonaj_ruch(polozenie); return 1; }
    if (znajdz_ukos(polozenie,1,1)==1)  { wykonaj_ruch(polozenie); return 1; }
    if (znajdz_ukos(polozenie,1,0)==1)  { wykonaj_ruch(polozenie); return 1; }
    if (znajdz_ukos(polozenie,0,1)==1)  { wykonaj_ruch(polozenie); return 1; }
    if (znajdz_ukos(polozenie,0,0)==1)  { wykonaj_ruch(polozenie); return 1; }

    return 0;
}
