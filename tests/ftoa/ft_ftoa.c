#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int         ft_inter_len(long long inter)
{
    int     i;

    i = 0;
    if (inter <= 0)
    {
        inter = inter * (-1);
        i++;
    }
    while (inter > 0)
    {
        inter = inter / 10;
        i++;
    }
    return (i);
}

/* at first we are dividing fractional and integer
** of input number;
** find length of integer numbers. Count of fractional
** numbers will be like precision + '\0' and  + '.';
** 
*/

char                *ft_ftoa(double num, long long p)
{
    double          fraction;
    long long       inter;
    double          tmp;
    char            *str;
    int             len;
    int             i;
    int             tmp2;
    int             len2;
    i = 0;
    inter = (long long)num;
    tmp = (double)inter;
    fraction = num - tmp;
    len = ft_inter_len(inter);
    if (!(str = (char *)malloc(sizeof(char) * (len + p + 2))))
        return (NULL);
    len2 = len + 1;
    if (inter == 0)
    {
        str[0] = '0';
        str[len] = '.';
        len++;
    }
    else
    {
        str[len--] = '.';
        while (i <= len)
        {
          str[len] = inter % 10 + '0';
          inter /= 10;
          len--;
        }
    }
    while (i < p)
    {
      fraction = fraction * 10;
      tmp2 = (int)fraction;
      str[len2++] = tmp2 + '0';
      fraction = fraction - tmp2;
      i++;
    }
  if (fraction > 0.5)
  {
      str[p + 1] = str[p + 1] + 1;
//      str[p + 1] = 0;
  }
  str[len2] = '\0';
    return (str);
}

int main() {

  float a;
  char  *b;
  a = 12.3457;
  b = ft_ftoa(a, 6);
  printf("%s\n", b);
  printf("%f\n", a);
  return 0;
}