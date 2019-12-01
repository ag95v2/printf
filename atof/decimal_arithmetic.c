#include "ft_fp.h"

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
		if (b->start > b->end)
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
**	both ends are temporarily shifted
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
