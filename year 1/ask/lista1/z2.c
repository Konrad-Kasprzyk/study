#include <stdio.h>
#include <stdlib.h>



int main()
{
    int i=6711;
    int a, b, c;
    a=i&0x55555555;
    b=(i>>1)&0x55555555;
    c=a+b;
    a=c&0x33333333;
    b=(c>>2)&0x33333333;
    c=a+b;
    a=c&0x0F0F0F0F;
    b=(c>>4)&0x0F0F0F0F;
    c=a+b;
    a=c&0x00FF00FF;
    b=(c>>8)&0x00FF00FF; // szesnastki
    c=a+b;
    c=c+(c>>16);
    printf("%d",c);



    return 0;
}
