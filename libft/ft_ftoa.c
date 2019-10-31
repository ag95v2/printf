
#include <stdlib.h>
#include <stdio.h>

static    int            ft_sym(long long int n)
{
    if (n < 0)
        return (-n);
    else
        return (n);
}

static    int            ft_CounterTillPoint(long long int n)
{
    int        c;

    if (n <= 0)
        c = 1;
    else
        c = 0;
    while (n)
    {
        n = n / 10;
        c++;
    }
    c++;
    return (c);
}

char                *ft_ftoa(float num)
{
    int                len;
    char            *res;
    long long int             n;
    int             i;
    
    i = 0;
    n = num * 1000000;
    len = ft_CounterTillPoint(n);
    if (!(res = malloc(sizeof(char) * (len + 1))))
        return (NULL);  
    if (num < 0)
        res[0] = '-';
    res[len] = '\0';
    len--;
    while (n)
    {
      if (i == 6)
      {
        res[len] = '.';
        len--;
      }
      res[len] = ft_sym(n % 10) + '0';
      n = n / 10;
      len--;
      i++;
    }
    return (res);
}

int     main(void)
{
    float num = -214748368.123123;
    printf("%s\n", ft_ftoa(num));
    printf("%f\n", num);
    return (0);
}