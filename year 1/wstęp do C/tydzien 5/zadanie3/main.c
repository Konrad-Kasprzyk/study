#include <stdio.h>
#include <stdlib.h>

void rysuj(char x)
{
    switch (x)
    {
        case 'a' :
        printf("a");
        break;

    }

}

int main()
{
    int i,j;
    int tab[20][20];
    for (i=0;i<20;i++)
        for (j=0;j<20;j++)
            tab[i][j]=0;
            printf("%d",tab[10][5]);
            rysuj('a');
    char tablica[5][5];
    printf("%d",tablica[3][4]);
    return 0;
}
