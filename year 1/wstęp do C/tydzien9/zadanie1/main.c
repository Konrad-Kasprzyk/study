// Konrad Kasprzyk

#include <stdio.h>
#include <stdlib.h>

int licz_wiersze(FILE *zrodlo)
{
    int licznik=0;
    char x;
    while ((x=fgetc(zrodlo))!=EOF)
        if (x=='\n') licznik++;
    rewind(zrodlo);
    return licznik;

}

int main(int argc,char *argv[])
{
    char napis[1000],*result;
    if (argc<4) printf("za malo argumentow, podaj nazwe programu, nazwe pilku gdzie zapisac wynik, liczbe wierszy, nazwy plikow do odczytania\n");
    FILE *wynik,*zrodlo;
     wynik=fopen(argv[1],"w");
     if (wynik==NULL) { printf("Nie udalo sie otworzyc wyniku \n"); return 1; }
     int n,i,j;
     n=atoi(argv[2]);
     for (i=3;i<argc;i++)
     {
        zrodlo=fopen(argv[i],"r");
        if (zrodlo==NULL) { fprintf(wynik,"\nNie udalo sie otworzyc piku zrodlowego nr %d \n",i); continue; }
        fprintf(wynik,"%s",argv[i]);
        fprintf(wynik," (%d)\n\n",licz_wiersze(zrodlo));
        for(j=0;j<n;j++)
        {
           result=fgets(napis,1000,zrodlo);
          if (result!=NULL)  fprintf(wynik,"%s",napis);
            else break;
        }
            fclose(zrodlo);
        fprintf(wynik,"\n");
     }
    fclose(wynik);
    return 0;
}
