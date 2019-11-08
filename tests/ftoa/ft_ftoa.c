/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:13:48 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/08 20:17:05 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int			ft_inter_len(long long inter)
{
	int		i;

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

struct var_ftoa
{
    long double fraction;
    long long   inter;
    long double tmp;
    char        *str;
    int         lenTillDot;
    int				i;
	int				tmp2;
	int				lenAfDot;
};

char                *ft_rounding_up(long double fraction, char *str, int lenAfDot)
{
    int             o;

    o = 0;
    if (fraction >= 0.5 && str[lenAfDot - 1] != '9')
    {
        str[lenAfDot - 1] += 1;
    }
    if (fraction >= 0.5 && str[lenAfDot - 1] == '9')
    {
        while(str[lenAfDot - 1] == '9')
        {
            str[lenAfDot - 1] = '0';
            o++;
        }
    }
    str[lenAfDot] = '\0';
    return (str);
}
char                *ft_ftoa(double num, long long p)
{
    struct var_ftoa            f;

    f.i = 0;
    f.inter = (long long)num;
    f.tmp = (double)f.inter;
    f.fraction = num - f.tmp;
    f.lenTillDot = ft_inter_len(f.inter);
    if (!(f.str = (char *)malloc(sizeof(char) * (f.lenTillDot + p + 2))))
        return (NULL);
    f.lenAfDot = f.lenTillDot + 1;
    if (f.inter == 0)
    {
        f.str[0] = '0';
        f.str[f.lenTillDot] = '.';
        f.lenTillDot++;
    }
    else
    {
        f.str[f.lenTillDot--] = '.';
        while (f.i <= f.lenTillDot)
        {
            f.str[f.lenTillDot] = f.inter % 10 + '0';
            f.inter /= 10;
            f.lenTillDot--;
        }
    }
    while (f.i < p)
    {
        f.fraction = f.fraction * 10;
        f.tmp2 = (int)f.fraction;
        f.str[f.lenAfDot++] = f.tmp2 + '0';
        f.fraction = f.fraction - f.tmp2;
        f.i++;
    }
    return (ft_rounding_up(f.fraction, f.str, f.lenAfDot));
}

int main() {
    float a;
    char  *b;
    a = 11;
    b = ft_ftoa(a, 8);
    printf("%s\n", b);
    printf("%1.8f\n", a);
    return 0;
}
