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

static int	copy_digits_numbers(char *src, char *dst)
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
	repr->after_dot = nchar_after_dot(s);
	repr->end = repr->buff + LD_MAX_DIGITS - 1; //end points to last digit!
	repr->start = repr->end - ndigits(s) + 1;
	copy_digits_numbers(s, repr->start);
}
