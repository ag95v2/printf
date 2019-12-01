/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/29 14:55:10 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"

/*
** Than to fill string with fractional numbers;
*/

char		*f_fill_fractional(t_varfloat *f)
{
	f->i = 0;
	(f->fractional < 0) ? f->fractional *= -1 : 0;
	while (f->i < 40)
	{
		f->fractional *= 10;
		f->tmp2 = (int)f->fractional;
		f->string[f->lenaf++] = f->tmp2 + '0';
		f->fractional = f->fractional - f->tmp2;
		f->i++;
	}
	return (f->string);
}

/*
** for integer = 0 and some numbers in fracitonal
*/

char		*f_fill_zero_fractional(t_varfloat *f)
{
	if (f->fractional < 0)
	{
		f->string[0] = '-';
		f->string[f->lenbef] = '0';
		f->string[f->lenbef + 1] = '.';
		f->lenaf++;
	}
	else
		f->string[f->lenbef - 1] = '0';
	return (f_fill_fractional(f));
}

/*
**  Our goal fill the string if input number less than 0;
**  taking module of numbers;
**  Put dot; Put minus;
**  In cycle adding ever number to our string
**  through receiving the remainder;
**  After filling integer with minus filling fractional of
**  number.
*/

char		*f_fill_integer_min(t_varfloat *f)
{
	if (f->integer == 0 && f->fractional < 0)
		return (f_fill_zero_fractional(f));
	else
	{
		f->string[f->lenbef--] = '.';
		f->string[0] = '-';
	}
	f->integer *= -1;
	while (0 < f->lenbef)
	{
		f->string[f->lenbef--] = f->integer % 10 + '0';
		f->integer /= 10;
	}
	return (f_fill_fractional(f));
}

char		*f_fill_integer(t_varfloat *f)
{
	f->string[f->lenbef--] = '.';
	while (0 <= f->lenbef)
	{
		f->string[f->lenbef--] = f->integer % 10 + '0';
		f->integer /= 10;
	}
	return (f_fill_fractional(f));
}

char		*ftoa(long double num)
{
	t_varfloat f;

	f.sym = 0;
	if (num < 0)
		f.sym = 1;
	f.integer = (long long)num;
	f.tmp = num - f.integer;
	f.fractional = f.tmp;
	f.lenbef = ft_inter_len(num);
	f.lenaf = f.lenbef + 1;
	f.cp_lenbef = f.lenbef;
	f.cp_lenaf = f.lenaf;
	f.cp_fractional = f.fractional;
	f.cp_integer = f.integer;
	if (!(f.string = (char *)malloc(sizeof(char) * (f.lenbef + 2 + 40))))
		return (NULL);
	if (f.integer < 0 || f.fractional < 0)
		return (f_fill_integer_min(&f));
	else
		return (f_fill_integer(&f));
	return (NULL);
}
