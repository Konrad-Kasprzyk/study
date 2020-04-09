//  UWAGA !!! sprawdz co sie dzieje jak w wierszu sa same biale znaki

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int spr(char tab[],char tab2[])
{
    int i,a,b,l=0;
    a=strlen(tab);
    b=strlen(tab2);
    if (a>=b)
    {
      for (i=0;i<b;i++)
        if(tab[i]!=tab2[i]) {l=1; break; }
        //printf("i= %d\n",i);
      if(l==0)
        {
            for(i=0;i<a-b;i++)
                if(tab[b+i]!=' ' && tab[b+i]!='\t' && tab[b+i]!= '\n') { l=1; break; }
        }
    }
    if (b>a)
    {
      for (i=0;i<a;i++)
        if(tab[i]!=tab2[i]) {l=1; break; }

      if(l==0)
        {
            for(i=0;i<b-a;i++)
                if(tab2[a+i]!=' ' && tab2[a+i]!='\t' && tab2[a+i]!= '\n') { l=1; break; }
        }
    }
    return l;
}

int main()
{


int i=0;
int a,l;
char c;
char string[6000];
char string2[6000];

c=getchar();
if (c=='\n') string[i]=c;
if (c==EOF) return 1;

while(c!='\n'&& c!='\0')
{
    string[i]=c;
    i++;
    c=getchar();
}
string[i]='\0';

c=getchar();

i=0;
if (c=='\n') string2[i]=c;
if (c==EOF) return 1;

while(c!='\n'&& c!='\0')
{
    string2[i]=c;
    i++;
    c=getchar();
}
string2[i]='\0';

if(spr(string,string2)==1) printf("%s\n",string);


while(1>0)
{
a=strlen(string2);

for (l=0;l<=a;l++)
    {
        string[l]=string2[l];
    }

c=getchar();
if (c==EOF) break;
i=0;
while(c!='\n' && c!='\0')
{
    string2[i]=c;
    i++;
    c=getchar();
}
string2[i]='\0';

if(spr(string,string2)==1) printf("%s\n",string);

}
printf("%s\n",string2);
    return 0;
}
