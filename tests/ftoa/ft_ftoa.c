/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:13:48 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/08 23:22:06 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "printf.h"

struct	varftoa
{
	long double		fraction;
	long long		inter;
	long double		tmp;
	char			*str;
	int				len_till_dot;
	int				i;
	int				len_af_dot;
};

int	ft_inter_len(long long inter)
{
	int				i;

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

/* 
** here we have some problem. Our function not rounding up
** to integer, when last fractional number is 9.
*/

char	*ft_rounding_up(long double fraction, char *str, int len_af_dot)
{
	if (fraction >= 0.5 && str[len_af_dot - 1] != '9')
	{
		str[len_af_dot - 1] += 1;
	}
	if (fraction >= 0.5 && str[len_af_dot - 1] == '9')
	{
		while (str[len_af_dot - 1] == '9')
		{
			str[len_af_dot - 1] = '0';
			str[len_af_dot - 2] += 1;
		}
	}
	str[len_af_dot] = '\0';
	return (str);
}

char	*ft_fill_fraction(long double fraction, char *str, \
			long long p, int len_af_dot)
{
	long long		tmp2;
	int				i;

	i = 0;
	while (i < p)
	{
		fraction = fraction * 10;
		tmp2 = (int)fraction;
		str[len_af_dot++] = tmp2 + '0';
		fraction = fraction - tmp2;
		i++;
	}
	return (ft_rounding_up(fraction, str, len_af_dot));
}

char	*ft_pr_zero(long double fraction, long long inter, \
				char *str, int len_till_dot)
{
	if (fraction >= 0,95)
		inter = inter + 1;
		str[len_till_dot--] = '\0';
	while (0 <= len_till_dot)
	{
		str[len_till_dot--] = inter % 10 + '0';
		inter /= 10;
	}
	if (inter < 0)
		str[0] = '-';
	return (str);
}

char	*ft_inter_minus(long double fraction, long long inter, char *str, \
							 int len_till_dot, int p)
{
	int		sym;
	int		len_af_dot;

	len_af_dot = len_till_dot + 1;
	sym = 0;
	sym = 1;
	fraction *= -1;
	str[len_till_dot--] = '.';
	str[0] = '-';
	if (inter == -0)
	{
		str[1] = '0';
		str[0] = '.';
		len_till_dot += 2;
	}
	inter *= -1;
	while (0 < len_till_dot)
	{
		str[len_till_dot--] = inter % 10 + '0';
		inter /= 10;
	}
	return (ft_fill_fraction(fraction, str, p, len_af_dot));
}

char	*ft_fill_inter(long long inter, char *str, int len_till_dot, int p, double long fraction)
{
	int		len_af_dot;

	len_af_dot = len_till_dot + 1;
	if (p == 0)
		return (ft_pr_zero(fraction, inter, str, len_till_dot));
	if (inter < 0 || fraction < 0)
		return (ft_inter_minus(fraction, inter, str, len_till_dot, p));
	if (inter == 0)
	{
		str[0] = '0';
		str[len_till_dot] = '.';
		len_till_dot++;
	}
	else
	{
		str[len_till_dot--] = '.';
		while (0 <= len_till_dot)
		{
			str[len_till_dot--] = inter % 10 + '0';
			inter /= 10;
		}
	}
	return (ft_fill_fraction(fraction, str, p, len_af_dot));
}

/* 
** At header was created structure with variables varftoa
** Our function taking double even if input is float
** dividing fractional and integer part of number.
** checking integer numbers and in other function fiiling
** fractional part.
*/

char	*ft_ftoa(long double num, long long p)
{
	struct varftoa	f;

	f.inter = (long long)num;
	f.tmp = (long double)f.inter;
	f.fraction = num - f.tmp;
	f.len_till_dot = ft_inter_len(f.inter);
	if (!(f.str = (char *)malloc(sizeof(char) * (f.len_till_dot + p + 2))))
		return (NULL);
	return (ft_fill_inter(f.inter, f.str, f.len_till_dot, p, f.fraction));
}
int main(void)
{
    float   a;
    char    *b;

    a = -13123.96;
    printf("GENERAL %0.1f\n", a);
    b = ft_ftoa(a, 1);
    printf("MY      %s\n", b);
    return (0);
}
