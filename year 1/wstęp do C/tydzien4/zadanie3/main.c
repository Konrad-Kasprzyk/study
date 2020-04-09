#include <stdio.h>
#include <stdlib.h>

void wczytaj_tab(int tab[][7],int l,int komorka)
{
    int a,b;
    scanf("%d",&a);
    scanf("%d",&b);
    a=a*60;
    tab[l][komorka]=a+b;
}

void sprawdz_2(int l,int czas[][7],int n_odj,int ile_1)
{
    int a,b;
    a=czas[l][3]-(czas[l][1]+ile_1);
    if (a<0)
    {
        if (a%1440==0) a=0;
        else
        {
            a=a%1440;
            a=a+1440;
        }
    }
    b=n_odj-(czas[l][1]+ile_1);
    if (b<0)
    {
        if (b%1440==0) b=0;
        else
        {
            b=b%1440;
            b=b+1440;
        }
    }
    if (b<a)    czas[l][3]=n_odj;
}
void sprawdz_1(int l,int czas[][7],int n_odj,int ile_1)
{
    int a,b;
    a=czas[l][1]-(czas[l][0]+ile_1);
    if (a<0)
    {
        if (a%1440==0) a=0;
        else
        {
            a=a%1440;
            a=a+1440;
        }
    }
    b=n_odj-(czas[l][0]+ile_1);
    if (b<0)
    {
        if (b%1440==0) b=0;
        else
        {
            b=b%1440;
            b=b+1440;
        }
    }
    if (b<a)    czas[l][1]=n_odj;
}


int wczytaj_n_odj()
{
    int a,b;
    scanf("%d",&a);
    scanf("%d",&b);
    a=a*60;
    return a+b;
}

int main()
{
    int ile_przystankow,czas_1,ile_1,czas_2,ile_2,czas_3,ile_3,i,l,n_odj,min,p;
    scanf("%d",&ile_przystankow);
    scanf("%d",&czas_1);
    scanf("%d",&ile_1);
    int tab[ile_1][7];
    for (i=0; i<ile_1; i++)
        wczytaj_tab(tab,i,0);
    if (ile_przystankow == 1)
    {
        printf("%d ",tab[0][0]/60);
        printf("%d ",tab[0][0]%60);
        printf("%d ",ile_1/60);
        printf("%d",ile_1%60);
        return 5;
    }
    scanf("%d",&czas_2);
    scanf("%d",&ile_2);
    n_odj=wczytaj_n_odj();
    for (i=0; i<ile_1; i++)
    {
        tab[i][1]=n_odj;
        tab[i][2]=czas_2;
    }
    if (ile_2>1)
        for (l=0; l<ile_2-1; l++)
        {
            n_odj=wczytaj_n_odj();
            for (i=0; i<ile_1; i++)
                sprawdz_1(i,tab,n_odj,czas_1);
        }
    for (i=0; i<ile_1; i++)
    {
        tab[i][6]=tab[i][1]-tab[i][0];
        if (tab[i][6]<0) tab[i][6]+=1440;
    }
    if (ile_przystankow>2)
    {
        while(ile_przystankow>2)
        {
            scanf("%d",&czas_3);
            scanf("%d",&ile_3);
            n_odj=wczytaj_n_odj();
            for (i=0; i<ile_1; i++)
            {
                tab[i][3]=n_odj;
                tab[i][4]=czas_3;
            }
            if (ile_3>1)
                for (l=0; l<ile_3-1; l++)
                {
                    n_odj=wczytaj_n_odj();
                    for (i=0; i<ile_1; i++)
                        sprawdz_2(i,tab,n_odj,czas_2);
                }
            for (i=0; i<ile_1; i++)
            {
                p=tab[i][3]-tab[i][1];
                if (p<0) p+=1440;
                tab[i][6]+=p;
            }
            for (i=0; i<ile_1; i++)
            {
                tab[i][1]=tab[i][3];
                tab[i][2]=czas_3;
            }
            ile_przystankow--;
        }
        for (i=0; i<ile_1; i++)
        {
            tab[i][6]+=czas_3;
        }
        min=tab[0][6];
        for (i=0; i<ile_1; i++)
        {
            tab[i][5]=tab[i][6];
            if (tab[i][5]<0) tab[i][5]+=1440;
            if (tab[i][5]<min) min=tab[i][5];
        }
        for (i=0; i<ile_1; i++)
            if (tab[i][5]==min)
            {
                printf("%d ",tab[i][0]/60);
                printf("%d ",tab[i][0]%60);
                printf("%d ",tab[i][5]/60);
                printf("%d",tab[i][5]%60);
                return 1;
            }
    }
    else
    {
        min=(tab[0][1]+tab[0][2])-tab[0][0];
        if (min<0) min=min+1440;
        for (i=0; i<ile_1; i++)
        {
            tab[i][5]=(tab[i][1]+tab[i][2])-tab[i][0];
            if (tab[i][5]<0) tab[i][5]+=1440;
            if (tab[i][5]<min) min=tab[i][5];
        }
        for (i=0; i<ile_1; i++)
            if (tab[i][5]==min)
            {
                printf("%d ",tab[i][0]/60);
                printf("%d ",tab[i][0]%60);
                printf("%d ",tab[i][5]/60);
                printf("%d",tab[i][5]%60);
                return 2;
            }
    }
    return 0;
}
