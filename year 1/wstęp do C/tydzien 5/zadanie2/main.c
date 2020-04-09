#include <stdio.h>
#include <stdlib.h>

int main()
{
   char tab[10][50];
   int i;
   for (i=0;i<5;i++)
   tab[i]="alama kota";
   for (i=0;i<5;i++)
   printf("%s\n",tab[i]);
}
