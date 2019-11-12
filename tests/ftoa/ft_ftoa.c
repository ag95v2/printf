 
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

/* DON't work with MINUS*/



#include <stdio.h>
#include <stdlib.h>

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

/* 
** At header was created structure with variables varftoa
** Our function taking double even if input is float
** dividing fractional and integer part of number.
** checking integer numbers and in other function fiiling
** fractional part.
*/

char	*ft_ftoa(double num, long long p)
{
	struct varftoa	f;

	f.inter = (long long)num;
	f.tmp = (double)f.inter;
	f.fraction = num - f.tmp;
	f.len_till_dot = ft_inter_len(f.inter);
	if (!(f.str = (char *)malloc(sizeof(char) * (f.len_till_dot + p + 2))))
		return (NULL);
	if (num < 0)
	{
		f.str[0] = '-';
		f.inter *= -1;
		f.fraction *= -1;
	}
	f.len_af_dot = f.len_till_dot + 1;
	if (p == 0)
	{
		if (f.fraction >= 0.95)
			f.inter = f.inter + 1;
		f.str[f.len_till_dot--] = '\0';
		while (0 < f.len_till_dot)
		{
			f.str[f.len_till_dot--] = f.inter % 10 + '0';
			f.inter /= 10;
		}
		return (f.str);
	}
	if (f.inter == 0)
	{
		f.str[0] = '0';
		f.str[f.len_till_dot] = '.';
		f.len_till_dot++;
	}
	else
	{
		f.str[f.len_till_dot--] = '.';
		while (0 <= f.len_till_dot) //if change <= to < - function wll not work;
		{
			f.str[f.len_till_dot--] = f.inter % 10 + '0';
			f.inter /= 10;
		}
		(f.inter < 0) ? f.str[0] = '-' : -1;
	}
	return (ft_fill_fraction(f.fraction, f.str, p, f.len_af_dot));
}

int	main(void)
{
	float			a;
	char			*b;

	a = -1234.5678;
	printf("GENERAL: %1.6f\n", a);
	b = ft_ftoa(a, 6);
	printf("MY:      %s\n", b);
	return (0);
}