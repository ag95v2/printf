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
  if (fraction >= 0.5 && str[len2 - 1] != '9')
  {
      str[len2 - 1] += 1;
//      str[p + 1] = 0;
  }
  int o = 0;
  if (fraction >= 0.5 && str[len2 - 1] == '9')
  {
      while(str[len2 - 1] == '9')
      {
          str[len2 - 1] = '0';
          len2--;
          o++;
      }
  }
  str[len2] = '\0';
    return (str);
}

int main() {
  float a;
  char  *b;
  a = 123.129999;
  b = ft_ftoa(a, 2);
  printf("%s\n", b);
  printf("%1.2f\n", a);
  return 0;
}

http://pythontutor.com/visualize.html#code=%23include%20%3Cstring.h%3E%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0A%0Aint%20%20%20%20%20%20%20%20%20ft_inter_len%28long%20long%20inter%29%0A%7B%0A%20%20%20%20int%20%20%20%20%20i%3B%0A%0A%20%20%20%20i%20%3D%200%3B%0A%20%20%20%20if%20%28inter%20%3C%3D%200%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20inter%20%3D%20inter%20*%20%28-1%29%3B%0A%20%20%20%20%20%20%20%20i%2B%2B%3B%0A%20%20%20%20%7D%0A%20%20%20%20while%20%28inter%20%3E%200%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20inter%20%3D%20inter%20/%2010%3B%0A%20%20%20%20%20%20%20%20i%2B%2B%3B%0A%20%20%20%20%7D%0A%20%20%20%20return%20%28i%29%3B%0A%7D%0A%0A/*%20at%20first%20we%20are%20dividing%20fractional%20and%20integer%0A**%20of%20input%20number%3B%0A**%20find%20length%20of%20integer%20numbers.%20Count%20of%20fractional%0A**%20numbers%20will%20be%20like%20precision%20%2B%20'%5C0'%20and%20%20%2B%20'.'%3B%0A**%20%0A*/%0A%0Achar%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20*ft_ftoa%28double%20num,%20long%20long%20p%29%0A%7B%0A%20%20%20%20double%20%20%20%20%20%20%20%20%20%20fraction%3B%0A%20%20%20%20long%20long%20%20%20%20%20%20%20inter%3B%0A%20%20%20%20double%20%20%20%20%20%20%20%20%20%20tmp%3B%0A%20%20%20%20char%20%20%20%20%20%20%20%20%20%20%20%20*str%3B%0A%20%20%20%20int%20%20%20%20%20%20%20%20%20%20%20%20%20len%3B%0A%20%20%20%20int%20%20%20%20%20%20%20%20%20%20%20%20%20i%3B%0A%20%20%20%20int%20%20%20%20%20%20%20%20%20%20%20%20%20tmp2%3B%0A%20%20%20%20int%20%20%20%20%20%20%20%20%20%20%20%20%20len2%3B%0A%20%20%20%20i%20%3D%200%3B%0A%0A%20%20%20%20inter%20%3D%20%28long%20long%29num%3B%0A%20%20%20%20tmp%20%3D%20%28double%29inter%3B%0A%20%20%20%20fraction%20%3D%20num%20-%20tmp%3B%0A%20%20%20%20len%20%3D%20ft_inter_len%28inter%29%3B%0A%20%20%20%20if%20%28!%28str%20%3D%20%28char%20*%29malloc%28sizeof%28char%29%20*%20%28len%20%2B%20p%20%2B%202%29%29%29%29%0A%20%20%20%20%20%20%20%20return%20%28NULL%29%3B%0A%20%20%20%20len2%20%3D%20len%20%2B%201%3B%0A%20%20%20%20if%20%28inter%20%3D%3D%200%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20str%5B0%5D%20%3D%20'0'%3B%0A%20%20%20%20%20%20%20%20str%5Blen%5D%20%3D%20'.'%3B%0A%20%20%20%20%20%20%20%20len%2B%2B%3B%0A%20%20%20%20%7D%0A%20%20%20%20else%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20str%5Blen--%5D%20%3D%20'.'%3B%0A%20%20%20%20%20%20%20%20while%20%28i%20%3C%3D%20len%29%0A%20%20%20%20%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20%20%20str%5Blen%5D%20%3D%20inter%20%25%2010%20%2B%20'0'%3B%0A%20%20%20%20%20%20%20%20%20%20inter%20/%3D%2010%3B%0A%20%20%20%20%20%20%20%20%20%20len--%3B%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%7D%0A%20%20%20%20while%20%28i%20%3C%20p%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20fraction%20%3D%20fraction%20*%2010%3B%0A%20%20%20%20%20%20tmp2%20%3D%20%28int%29fraction%3B%0A%20%20%20%20%20%20str%5Blen2%2B%2B%5D%20%3D%20tmp2%20%2B%20'0'%3B%0A%20%20%20%20%20%20fraction%20%3D%20fraction%20-%20tmp2%3B%0A%20%20%20%20%20%20i%2B%2B%3B%0A%20%20%20%20%7D%0A%20%20if%20%28fraction%20%3E%3D%200.5%20%26%26%20str%5Blen2%20-%201%5D%20!%3D%20'9'%29%0A%20%20%7B%0A%20%20%20%20%20%20str%5Blen2%20-%201%5D%20%2B%3D%201%3B%0A//%20%20%20%20%20%20str%5Bp%20%2B%201%5D%20%3D%200%3B%0A%20%20%7D%0A%20%20int%20o%20%3D%200%3B%0A%20%20if%20%28fraction%20%3E%3D%200.5%20%26%26%20str%5Blen2%20-%201%5D%20%3D%3D%20'9'%29%0A%20%20%7B%0A%20%20%20%20%20%20while%28str%5Blen2%20-%201%5D%20%3D%3D%20'9'%29%0A%20%20%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20%20%20str%5Blen2%20-%201%5D%20%3D%20'0'%3B%0A%20%20%20%20%20%20%20%20%20%20len2--%3B%0A%20%20%20%20%20%20%20%20%20%20o%2B%2B%3B%0A%20%20%20%20%20%20%7D%0A%20%20%7D%0A%20%20str%5Blen2%5D%20%3D%20'%5C0'%3B%0A%20%20%20%20return%20%28str%29%3B%0A%7D%0A%0Aint%20main%28%29%20%7B%0A%20%20float%20a%3B%0A%20%20char%20%20*b%3B%0A%20%20a%20%3D%20123.129999%3B%0A%20%20b%20%3D%20ft_ftoa%28a,%202%29%3B%0A%20%20printf%28%22%25s%5Cn%22,%20b%29%3B%0A%20%20printf%28%22%251.2f%5Cn%22,%20a%29%3B%0A%20%20return%200%3B%0A%7D&cumulative=false&heapPrimitives=nevernest&mode=edit&origin=opt-frontend.js&py=c&rawInputLstJSON=%5B%5D&textReferences=false