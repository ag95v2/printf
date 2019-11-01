#include "prototypes.h"

char *flot(float x)
{
  int   n;
  int   i;
  int   k;
  char	*p;

  p = (char *)malloc(sizeof(char) * 20);
  k = 0;
  i = 0;
  n = (int)x;
  while(n > 0)
  {
     x/=10;
     n=(int)x;
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
    *(p+k) = '\0';
	return (p);
}
