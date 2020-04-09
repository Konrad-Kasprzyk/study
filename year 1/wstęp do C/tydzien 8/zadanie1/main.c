#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wllc.h"

int main()
{
    WLLC L,L2,L3,L4;
  /*  L=utworz();
    L2=utworz();
    L4=utworz();
    L=dl(5,L);
    L=dl(6,L);
    L2=dl(7,L2);
    L2=dl(8,L2);

    L=dl(9,L);
L3=WLLC_merge(L,L);
    drukuj(L3);
    printf("\n");
    drukuj(L2);
    printf("\n");
    L=dopisz_koniec(78,&L);
    drukuj(L);
     printf("\n");
     L4=dopisz_koniec(55,&L4);
      L4=dopisz_koniec(56,&L4);
     drukuj(L4);
      L2=dp(L3,L2);
      L=dp(L2,L);
      printf("\n");
      */
      L=utworz();
    L2=utworz();
     L3=utworz();
    L2=dp(L3,L2);
     L=dp(L2,L);
    L3=utworz();
    L4=utworz();

       L=dl(5,L);
        L=dl(6,L);
         L=dl(7,L);
         L=dp(L2,L);
        L2=dl(8,L2);
        L2=dl(9,L2);
        L3=dl(10,L3);
         L3=dl(11,L3);
       L3=dl(12,L3);
       L2=dp(L3,L2);
         L2=dl(13,L2);
         L2=dl(14,L2);

           L=dl(15,L);
           L=dl(16,L);
            L=dp(L2,L);
          // drukuj(L);
           printf("\n");
         //  drukuj(L2);
           printf("\n");
L4=WLLC_flat(L2);
    // drukuj(L4);
    //  drukuj(L);

        drukuj(L);
        printf("\n");
     L4=WLLC_flat(L);
     drukuj(L4);
    return 0;
}
