
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static	int			ft_sym(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t		i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static	int			ft_counter(int n)
{
	int		c;

	if (n <= 0)
		c = 1;
	else
		c = 0;
	while (n)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char				*ft_itoa(int n)
{
	int				len;
	char			*res;

	len = ft_counter(n);
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(res, "-2147483648"));
	if (n == 0)
		res[0] = '0';
	if (n < 0)
		res[0] = '-';
	res[len] = '\0';
	len--;
	while (n)
	{
		res[len] = ft_sym(n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (res);
}


char* ft_ftoa(double number)
{

    char* first;
    char string[50];
    char string_2[50];
    double  number_2,change;
	long int  fractional,decimal;


    decimal = (int) number;     //extracting decimal part form fractional

    number_2 = (double) decimal;

    change = number - number_2;

    fractional = change*1000; //extracting fractional part and changing it into integer

    ft_itoa(decimal);
    ft_itoa(fractional);

    strcat(string,".");                     //adding dot between numbers
    strcat(string,string_2);
    first = string;

    return (first);                           //returning final string
}