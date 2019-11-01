#include<stdio.h>

void flot(char* p, float x)
{
  int   n;
  int   i;
  int   k;
  
  k = 0;
  i = 0;
  n = (int)x;
  while(n > 0)
  {
     x/=10;
     n=(int)x; //взял целочисленное
     i++;
    }
    *(p+i) = '.';
    x *= 10;
    n = (int)x;
    x = x - n;
    while ((n > 0)||(i > k))
    {
        if(k == i)
        k++;
        *(p + k) ='0' + n;
        x *= 10;
        n = (int)x;
        x = x - n;
        k++;
    }
 /* Null-terminated string */
    *(p+k) = '\0';
}

int main()
{
  float x = 1.1231;
  char a[20]={};
  char* p=&a;

  printf("Enter the float value.\n");
  flot(p,x);
  printf("The value=%s\n",p);
  printf("The value=%f\n",x);
  return 0;
}