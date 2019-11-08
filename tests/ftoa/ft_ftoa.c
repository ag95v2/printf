/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:13:48 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/08 22:45:20 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

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

char	*ft_rounding_up(long double fraction, char *str, int len_af_dot)
{
	int				o;

	o = 0;
	if (fraction >= 0.5 && str[len_af_dot - 1] != '9')
	{
		str[len_af_dot - 1] += 1;
	}
	if (fraction >= 0.5 && str[len_af_dot - 1] == '9')
	{
		while (str[len_af_dot - 1] == '9')
		{
			str[len_af_dot - 1] = '0';
			o++;
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

char	*ft_ftoa(double num, long long p)
{
	struct varftoa	f;

	f.i = 0;
	f.inter = (long long)num;
	f.tmp = (double)f.inter;
	f.fraction = num - f.tmp;
	f.len_till_dot = ft_inter_len(f.inter);
	if (!(f.str = (char *)malloc(sizeof(char) * (f.len_till_dot + p + 2))))
		return (NULL);
    f.len_af_dot = f.len_till_dot + 1;
//	ft_fill_str(f.str, f.len_till_dot, f.inter, f.i)
    if (f.inter == 0)
	{
		f.str[0] = '0';
		f.str[f.len_till_dot] = '.';
		f.len_till_dot++;
	}
	else
	{
		f.str[f.len_till_dot--] = '.';
		while (f.i <= f.len_till_dot)
		{
			f.str[f.len_till_dot] = f.inter % 10 + '0';
			f.inter /= 10;
			f.len_till_dot--;
		}
	}
	return (ft_fill_fraction(f.fraction, f.str, p, f.len_af_dot));
}

int	main(void)
{
	float			a;
	char			*b;

	a = 213.11;
	b = ft_ftoa(a, 6);
	printf("%s\n", b);
	printf("%1.6f\n", a);
	return (0);
}
