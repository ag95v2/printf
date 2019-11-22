#include "printf.h"
#define DEFAULT_FLOAT_PRECISION 6

/*
**  Return string that contains n chars c
**	If n <= 0, return nonzero ptr to empty string
*/

char	*char_n_dup(char c, int n)
{
	char	*res;

	res = 0;
	if (n < 0)
		n = 0;
	if (n + 1 < n)
		return (0);
	res = ft_memalloc(n > 0 ? n + 1 : 1);
	if (!res)
		return (0);
	if (n <= 0)
		return (res);
	while (n--)
		res[n] = c;
	return (res);
}

int	is_signed_conversion(t_spec spec)
{
	if (spec.conv == 'i' || spec.conv == 'f' || spec.conv == 'd')
		return (1);
	return (0);
}

int	is_numeric(t_spec spec)
{
	if (\
		spec.conv == 'd' || spec.conv == 'i' || \
		spec.conv == 'o' || spec.conv == 'u' || \
		spec.conv == 'x' || spec.conv == 'X' || \
		spec.conv == 'f' \
	   )
		return (1);
	return (0);
}

int	is_nonfloat_numeric(t_spec spec)
{
	if (is_numeric(spec) || spec.conv != 'f')
		return (1);
	return (0);
}

/* return initial string */
char	*str_replace(char *s, char pattern, char replacement)
{
	char	*start;

	start = s;
	while (*s)
	{
		if (*s  == pattern)
			*s = replacement;
		s++;
	}
	return (start);
}

/*
**  Warning! 
**  s is always freed. suffix is always not freed
**	In case of NULL argument return NULL
*/

char	*add_suffix(char *s, char *suffix)
{
	int		len;
	char	*new;

	if (!s || !suffix)
	{
		free(s);
		return (0);
	}
	len = ft_strlen(s);
	new = ft_strnew(len + ft_strlen(suffix));
	if (!new)
	{
		free(s);
		return (0);
	}
	ft_strcpy(new, s);
	ft_strcpy(new + len, suffix);
	free(s);
	return (new);
}


/*
**  Warning! 
**  s is always freed. prefix is always not freed
**	In case of NULL argument return NULL
*/

char	*add_prefix(char *s, char *prefix)
{
	int		len;
	char	*new;

	if (!s || !prefix)
	{
		free (s);
		return (0);
	}
	len = ft_strlen(prefix);
	new = ft_strnew(len + ft_strlen(s));
	if (!new)
	{
		free(s);
		return (0);
	}
	ft_strcpy(new, prefix);
	ft_strcpy(new + len, s);
	free(s);
	return (new);
}

char	*prepend_zeros(char *s, int n)
{
	char	*prefix;
	
	if (!(prefix = char_n_dup('0', n)))
		return (0);
	s = add_prefix(s, prefix);
	free(prefix);
	return (s);
}

/*
**	Insert string src into n-th position of string dst
**	free src and dst
*/

char	*str_insert(char *dst, char *src, int pos)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strnew(ft_strlen(src) + ft_strlen(dst));
	if (!new)
		return (0);
	while (i < pos)
	{
		new[i] = dst[i];
		i++;
	}
	ft_strcat(new, src);
	ft_strcat(new, dst + i);
	free(src);
	free(dst);
	return (new);
}

int		only_zeros(char *s)
{
	while (*s)
		if (*s++ != '0')
			return (0);
	return (1);
}

char	*apply_hash(char *s, t_spec spec)
{
	if (((spec.conv == 'p')&& ft_strcmp(s, "(nil)")))
		return (add_prefix(s, "0x"));

	if (spec.flag_hash == 1 && spec.precision == 0 && spec.conv == 'o')
		return (add_prefix(s, "0"));
	if (spec.flag_hash != 1 || only_zeros(s))
		return (s);
	if (spec.conv == 'o' && s[0] != '0')
		return (add_prefix(s, "0"));
	if (\
			(spec.conv == 'x' && ft_strcmp(s, "0")) ||\
			((spec.conv == 'p')&& ft_strcmp(s, "(nil)")))
		return (add_prefix(s, "0x"));
	if (spec.conv == 'X' && ft_strcmp(s, "0"))
		return (add_prefix(s, "0X"));
	if (spec.conv == 'f' && !ft_strchr(s, '.'))
		return (add_suffix(s, ".0"));
	return (s);
}

char	*apply_plus(char *s, t_spec spec)
{
	if (spec.flag_plus != 1)
		return (s);
	if (is_signed_conversion(spec) && s[0] != '-')
		return (add_prefix(s, "+")); 
	// Man page says sign should always be + or -. How about 0??
	return (s);
}

char	*apply_space(char *s, t_spec spec)
{
	if (spec.flag_space != 1 || spec.flag_plus == 1)
		return (s);
	if (is_signed_conversion(spec) && s[0] != '-' )
		return (add_prefix(s, " ")); 
	// Man page says prefix should be added only for POSITIVE numbers
	// We reproduce bug and consider 0 as positive number
	return (s);
}

/*
**  "+" " " "#"
*/

char	*apply_numeric_flags(char *s, t_spec spec)
{
	if (spec.conv == 'p')
		return ((s = apply_hash(s, spec)));
	if (is_numeric(spec) &&\
		(s = apply_hash(s, spec)) &&\
		(s = apply_plus(s, spec)) &&\
		(s = apply_space(s, spec))\
	   )
		return (s);
	return (s);
}

/*
**	Return number of chars in string after dot
**	or 0 if no dot in char
*/

int	len_after_dot(char *s)
{
	while (*s && *s != '.')
		s++;
	return	(*s ? ft_strlen(++s) : 0);
	
}

/* 
**  Caller must provide a precision > than number of chars after dot
*/

char	*round_float(char *s, int precision)
{
	int		carry_bit;
	char	*digit;

	carry_bit = 0;
	digit = ft_strchr(s, '.') + precision + 1;
	if (*digit >= '5')
		carry_bit++;
	*digit = 0;
	while (carry_bit && digit != s)
	{
		digit--;
		if (*digit == '+' || *digit == '-' || *digit == '.')
			continue;
		if (*digit == '9') 
		{
			carry_bit = 1;
			*digit = '0';
		}
		else
		{
			(*digit)++;
			carry_bit = 0;
		}
	}
	if (carry_bit && digit == s)
		s = str_insert(s, ft_strdup("1"), ft_isdigit(*s) ? 0 : 1);
	if (precision == 0)
		return (str_replace(s, '.', 0));
	return (s);
}

char	*float_precision(char *s, t_spec spec)
{
	int		precision;
	int		nchar_after_dot;
	char	*suffix;

	precision = spec.precision;
	nchar_after_dot = len_after_dot(s);
	if (precision > nchar_after_dot)
	{
		if (nchar_after_dot == 0 &&
			!(s = add_suffix(s, ".")))
			return (0);
		suffix = char_n_dup('0', precision - nchar_after_dot);
		return(add_suffix(s, suffix));
	}
	if (precision < nchar_after_dot)
		s = round_float(s, precision);
	
	if (precision == 0 && spec.flag_hash)
		s = add_suffix(s, ".");
	//here dot is always in number if this function is called
	return (s);
}
/*
**	< 0 => uninitialized
**	for floats default is 6
*/

char	*apply_precision(char *s, t_spec spec)
{
	char	*zeros;

	if (spec.conv == 'p' && !ft_strcmp(s, "0"))
	{
		free(s);
		s = ft_strdup("(nil)");
	}
	if (spec.precision < 0 && spec.conv == 'f')
		spec.precision = DEFAULT_FLOAT_PRECISION;
	if (spec.precision < 0)
		return (s);
	if (spec.conv == 's')
	{
		s[spec.precision] = 0;
		return (s);
	}
	if (spec.conv == 'f')
		return (float_precision(s, spec));
	/* PRINT NOTHING IN THAT CASE */
	if (spec.precision == 0 && !ft_strcmp(s, "0"))
		return (str_replace(s, '0', 0));
	/* Insert zeros from the left to nonfloat numeric (after - if negative) */
	if (spec.precision > 0 && is_nonfloat_numeric(spec))
	{
		zeros = char_n_dup('0', spec.precision - ft_strlen(s) + (*s == '-'));
		return (str_insert( s,zeros, (*s == '-')? 1: 0));
	}
	return (s);
}

/*
**	Apply flag zero to different cases
*/

char	*apply_fzero(char *s, t_spec spec)
{
	int		nzeros;
	char	*zeros;

	nzeros = spec.width - ft_strlen(s);
	if (nzeros <= 0 || !is_numeric(spec))
		return (s);
	zeros = char_n_dup('0', nzeros);
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		return (str_insert(s, zeros, 2));
	if (s[0] == '-' || s[0] == '+' || spec.flag_space == 1)
		return (str_insert(s, zeros, 1));
	return (str_insert(s, zeros, 0));
}

char	*apply_fdash(char *s, t_spec spec)
{
	char	*spaces;
	int		len;

	len = ft_strlen(s);
	if (len >= spec.width)
		return (s);
	spaces = char_n_dup(' ', spec.width - len);
	return (spec.flag_dash ? add_suffix(s, spaces) : add_prefix(s, spaces));
}

/* 
**	Width and flags '0' and '-' are logically tied
*/

char	*apply_width(char *s, t_spec spec)
{
	if (spec.conv == '%')
		return (s);
	if (spec.flag_zero == 1 && (spec.precision <= 0 || spec.conv == 'f') \
			&& !spec.flag_dash)
		return (apply_fzero(s, spec));
	return (apply_fdash(s, spec));
}

/*
**  Modify only the copy of original string
**	Always return a copy. Copy always MUST be freed.
*/

char	*apply_spec(char *s, t_spec *spec)
{
	char	*new;

	if (\
		!(new = ft_strdup(s)) ||\
		!(new = apply_precision(new, *spec)) ||\
		!(new = apply_numeric_flags(new, *spec)) ||\
		!(new = apply_width(new, *spec)) \
		)
		return (0);
	if  (ft_strlen(s) == 0 && spec->conv == 'c')
		spec->stupid_c0_special_case = 1;
	return (new);
}
