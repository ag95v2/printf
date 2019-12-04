/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/04 17:31:47 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"

///////////////////NEW FTOA'S HEADER////////////////
#define LD_MAX_DIGITS 20000

typedef struct	s_decimal
{
	char		buff[LD_MAX_DIGITS];
	char		*end;
	char		*start;
	int			after_dot;
	int			is_negative;
}				t_decimal;

typedef struct	s_float
{
	unsigned long int	mant;
	unsigned short		exp;
	char				sign;
	unsigned long int	mant_mask;
	int					mask_shift;
	
}				t_float;

////////////////////////////////////////////////////

typedef struct		s_variablesforfloat
{
	char			*string;
	long long		integer;
	long double		fractional;
	long long		cp_integer;
	long double		cp_fractional;
	int				sym;
	long double		tmp;
	long long		lenbef;
	long long		lenaf;
	long long		cp_lenbef;
	long long		cp_lenaf;
	int				i;
	int				tmp2;
	int				number;
	int				p;
	char			*res;
}					t_varfloat;

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

char		*old_ftoa(long double num)
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

///////////////////////////////////////////////////////////////////////


static void	insert_point(int after_dot, char *s)
{
	char	tmp;

	while (*s)
		s++;
	if (after_dot == 0)
	{
		*s++ = '.';
		*s++ = '0';
		*s = 0;
		return ;
	}
	while (after_dot)
	{
		*(s + 1) = *s;
		after_dot--;
		s--;
	}
	*(s + 1) = *s;
	*s = '.';
}

int	to_ascii(t_decimal repr, char *s)
{
	int		i;
	int		n_digits;

	i = 0;
	if (repr.is_negative)
		s[i++] = '-';
	n_digits = repr.end - repr.start + 1;
	if (n_digits == repr.after_dot)
		s[i++] = '0';
	while (n_digits)
	{
		s[i++] = *(repr.start++) + '0';
		n_digits--;
	}
	s[i] = 0;
	insert_point(repr.after_dot, s);
	return (i);
}

static int	nchar_after_dot(char *s)
{
	int	n;

	n = 0;
	while (*s != '.' && *s)
		s++;
	if (*s)
		s++;
	while (*s++)
		n++;
	return (n);
}

static int	ndigits(char *s)
{
	int	n_digits;
	int	len;

	len = -1;
	n_digits = 0;
	while (s[++len])
	{
		if (s[len] >= '0' && s[len] <= '9')
			n_digits++;
	}
	return (n_digits);
}

static void	copy_digits_numbers(char *src, char *dst)
{
	while (*src)
	{
		if (*src >= '0' && *src <= '9')
		{
			*dst = *src - '0';
			dst++;
		}
		src++;
	}
}

/*
**	Fill repr
*/

void	positive_ascii_to(t_decimal *repr, char *s)
{
	repr->is_negative = 0;
	repr->after_dot = nchar_after_dot(s);
	repr->end = repr->buff + LD_MAX_DIGITS - 1; //end points to last digit!
	repr->start = repr->end - ndigits(s) + 1;
	copy_digits_numbers(s, repr->start);
}

/************************************************************
***************Addition functions below**********************
************************************************************/

/*
** return number of excessive digits
*/

static int	shift_excessive_digits(t_decimal *a, t_decimal *b, char *tmp)
{
	int	i;
	int	nchar_a;
	int	nchar_b;

	nchar_a = a->after_dot; 
	nchar_b = b->after_dot; 
	i = 0;
	while (nchar_a > nchar_b)
	{
		nchar_b++;
		tmp[i] = *(a->end);
		a->end--;
		i++;		
	}
	while (nchar_b > nchar_a)
	{
		nchar_a++;
		tmp[i] = *(b->end);
		b->end--;
		i++;		
	}
	return (i);
}

/* case when b ended */

static void	single_digit_a(t_decimal *a, char **res, int *carry)
{
	**res = (*(a->end) + *carry) % 10;
	*carry = (*(a->end) + *carry) / 10;
	a->end--;
	(*res)++;
}

/* case when a ended */

static void	single_digit_b(t_decimal *b, char **res, int *carry)
{
	**res = (*(b->end) + *carry) % 10;
	*carry = (*(b->end) + *carry) / 10;
	b->end--;
	(*res)++;
}

/* case when both numbers not ended */

static void	single_digit_both(t_decimal *a, t_decimal *b, char **res, int *carry)
{
	**res = (*(a->end) + *(b->end) + *carry) % 10;
	*carry = (*(a->end) + *(b->end) + *carry) / 10;
	a->end--;
	b->end--;
	(*res)++;
}

/*
**	Fill res with digits
**	Ignore possible overflow yet
**	res will be terminated by -1
*/

static void	adder_decimal(t_decimal *a, t_decimal *b, char *res)
{
	int		carry;

	carry = 0;
	while (a->start <= a->end || b->start <= b->end)
	{
		if (a->start > a->end)
			single_digit_b(b, &res, &carry);
		else if (b->start > b->end)
			single_digit_a(a, &res, &carry);
		else
			single_digit_both(a, b, &res, &carry);
	}
	carry ?	*(res++) = carry : ((*res) = -1);
	*res = -1;
}

static void	copy_from_buf(char *buf, t_decimal *a)
{
	a->start = a->end;
	while (*buf != -1)
	{
		*(a->start) = *buf;
		a->start--;
		buf++;
	}
	a->start++;
}

static int	max(int a, int b)
{
	return (a > b ? a : b);
}

/*
**  Add 2 numbers in-place (result is stored in a)
*/

void			add_positive_decimal(t_decimal *a, t_decimal *b)
{
	char	tmp[LD_MAX_DIGITS]; //inverse number will be stored here

	adder_decimal(a, b, tmp + shift_excessive_digits(a, b, tmp));
	a->end = a->buff + LD_MAX_DIGITS - 1;
	b->end = b->buff + LD_MAX_DIGITS - 1;
	copy_from_buf(tmp, a);
	a->after_dot = max(a->after_dot, b->after_dot);
}

/************************************************************
***************Multiplication functions below****************
************************************************************/

static void		mul_digit(t_decimal *a, t_decimal *b,\
		int degree, t_decimal *partial_product)
{
	int	carry;
	
	partial_product->end = partial_product->buff + LD_MAX_DIGITS - 1; //end points to last digit!
	partial_product->start = partial_product->end;
	while (degree--)
		*(partial_product->start--) = 0;
	carry = 0;
	while (a->start <= a->end)
	{
		*(partial_product->start) = (*(b->end) * *(a->end) + carry) % 10;
		carry = (*(b->end) * *(a->end) + carry) / 10;
		a->end--;
		partial_product->start--;
	}
	partial_product->start++;
	if (carry)
	{
		partial_product->start--; 
		*(partial_product->start) = carry;
	}
	a->end = a->buff + LD_MAX_DIGITS - 1; //end points to last digit!
}

void	copy_t_decimal(t_decimal *src, t_decimal *dst)
{
	char	*tmp;

	tmp = src->end;
	while (tmp >= src->start)
	{
		*(dst->end) = *tmp;
		dst->end--;
		tmp--;
	}
	dst->end++;
	dst->start = dst->end;
	dst->end = dst->buff + LD_MAX_DIGITS - 1; //end points to last digit!
	dst->after_dot = src->after_dot;
	dst->is_negative = src->is_negative;
}

static void adjust_dot_if_needed(t_decimal *a)
{
	while (a->after_dot > a->end - a->start + 1)
	{
		a->start--;
		*(a->start) = 0;
	}
}

/*
**  Multiply 2 DIFFERENT numbers in-place (result is stored in a)
**	In case of square, you need to copy  the first operand
*/

void			multiply_positive_decimal(t_decimal *a, t_decimal *b)
{
	t_decimal	total;
	t_decimal	partial_product;
	int			degree;
	int			after_dot_new;

	positive_ascii_to(&partial_product, "0");
	positive_ascii_to(&total, "0");
	degree = 0;
	while (b->end >= b->start)
	{
		if (*b->end)
		{
			mul_digit(a, b, degree, &partial_product);
			add_positive_decimal(&total, &partial_product);
		}
		b->end--;
		degree++;
	}
	b->end = b->buff + LD_MAX_DIGITS - 1; //end points to last digit!
	after_dot_new = a->after_dot + b->after_dot;
	copy_t_decimal(&total, a);
	a->after_dot = after_dot_new;
	adjust_dot_if_needed(a);
}

/************************************************************
***************Power functions below*************************
************************************************************/

void			init_t_decimal(t_decimal  *x)
{
	x->end = x->buff + LD_MAX_DIGITS - 1;
	x->start = x->end;
	x->after_dot = 0;
	x->is_negative = 0;
}

void			square_positive_decimal(t_decimal *x)
{
	t_decimal tmp;

	init_t_decimal(&tmp);
	copy_t_decimal(x, &tmp);
	multiply_positive_decimal(x, &tmp);
}

/*
**	Only positive powers
*/

void			power_positive_decimal(t_decimal *x, int pow)
{
	int			current_power;
	t_decimal	result;
	t_decimal	current_value;

	if (!pow)
		positive_ascii_to(x, "1");
	init_t_decimal(&current_value);
	positive_ascii_to(&result, "1");
	while (pow)
	{
		copy_t_decimal(x, &current_value);
		current_power = 1;
		while (current_power * 2 <= pow)
		{
			square_positive_decimal(&current_value);
			current_power *= 2;
		}
		pow -= current_power;
		multiply_positive_decimal(&result, &current_value);
	}
	copy_t_decimal(&result, x);
}


void	fill_t_float(long double x, t_float *num)
{
    num->mant = *((unsigned long int *)&x); 
	num->exp = *(unsigned short *)((char *)&x + sizeof(unsigned long int));
	num->sign = num->exp & (((unsigned short) 1) << 15);
	num->exp = num->exp & ((~((unsigned short) 0)) >> 1);
	num->mant_mask = (((unsigned long int) 1) << 63);
	num->mask_shift = 0;
}

int	abs(int x)
{
	return (x >= 0 ? x : -x);
}

char	*eval_power_sum(t_float *num, int power_of2)
{
	static char	res[LD_MAX_DIGITS];
	t_decimal	total;
	t_decimal	current;
	t_decimal	accum;

	positive_ascii_to(&accum, "0");
	positive_ascii_to(&total, power_of2 > 0 ? "2" : "0.5");
	power_positive_decimal(&total, abs(power_of2));
	while (num->mask_shift < 64)
	{
		if (num->mant_mask >> num->mask_shift & num->mant)
		{
			positive_ascii_to(&current, "0.5");
			power_positive_decimal(&current, num->mask_shift);
			multiply_positive_decimal(&current, &total);
			add_positive_decimal(&accum, &current);
		}
		num->mask_shift++;
	}
	if (num->sign)
		accum.is_negative = 1;
	to_ascii(accum, res);
	return (res);
}

char	*normal_case(t_float *num)
{
	return (eval_power_sum(num, num->exp - 16383));
}

char	*exp_all_zeros(t_float *num)
{
	if (!num->mant)
		return (num->sign ? "-0.0" : "0.0");
	return (eval_power_sum(num, -16382));
}

char	*exp_all_ones(t_float *num)
{
	//62-0 bits of mant ==0 
	if (!(num->mant & ~num->mant_mask))	
		return (num->sign ? "-inf" : "inf");
	return ("NaN");
}

char	*new_ftoa(long double x)
{
	t_float	num;

	fill_t_float(x, &num);
	if (!~((num.exp << 1) + 1))
		return (exp_all_ones(&num));
	else if (!(num.exp << 1))
		return (exp_all_zeros(&num));
	else
		return (normal_case(&num));
}



///////////////////////////////////////////////////////////////////////
int		main(void)
{
	double a = 0.87650894255l;
	printf("ORIGINAL: %f\n", a);
	printf("OLD FTOA: %s\n", old_ftoa(a));
	printf("NEW FTOA: %s\n", new_ftoa(a));

	return(0);
}

