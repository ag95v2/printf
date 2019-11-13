#include "printf.h"

/*
**	Fill all fields of structure with zeros.
*/

void		init_spec(t_spec *spec)
{
	spec->flag_zero = 0;
	spec->flag_hash = 0;
	spec->flag_plus = 0;
	spec->flag_dash = 0;
	spec->flag_space = 0;
	spec->width = 0;
	spec->precision = 0;
	spec->length = 0;
	spec->conv = 0;
}

void read_flag(const char c, t_spec *spec)
{
	if (c == '+')
		spec->flag_plus = 1;
	if (c == '-')
		spec->flag_dash = 1;
	if (c == ' ')
		spec->flag_space = 1;
	if (c == '#')
		spec->flag_hash = 1;
	if (c == '0')
		spec->flag_zero = 1;
}

/*
**	Read any nonnegative number of flags.
**	One flag can be mentioned more than once
**  No other chars expected here.
**	Return a pointer to first non-flag char in f
*/

const char	*read_flags(const char *f, t_spec *spec)
{
	while (*f == '+' || *f == '-' || *f == ' ' || *f == '#' || *f == '0')
		read_flag(*(f++), spec);
	return (f);
}

/*
**	Skip all digits if they exist in format spec.
**  Fill the field "width"
**	Return: ptr to first non-digit in f
*/

const char	*read_width(const char *f, t_spec *spec)
{
	if (ft_isdigit(*f))
		spec->width = ft_atoi(f);
	while (ft_isdigit(*f))
		f++;
	return (f);
}

/*
**	Skip all digits if they exist in format spec.
**  Fill the field "precision"
**	Return: ptr to first non-digit in f
*/

const char	*read_precision(const char *f, t_spec *spec)
{
	if (ft_isdigit(*f))
		spec->precision = ft_atoi(f);
	while (ft_isdigit(*(f++)))
		;
	return (f);
}

/*
**	Skip all digits if they exist in format spec.
**  Fill the field "length"
**	Return: ptr to first non-length specifier in f
**	UPD: peers say, that we must process multiple length specifiers 
**	and select max of them. Enum is ordered actually.
*/

const char	*read_length(const char *f, t_spec *spec)
{
	while (*f == 'l' || *f == 'L' || *f == 'h')
	{
		if (*f == 'l' && *(f + 1) == 'l' && spec->length < ll)
			spec->length = ll;
		if (*f == 'l' && *(f + 1) != 'l' && spec->length < l)
			spec->length = l;
		if (*f == 'h' && *(f + 1) == 'h' && spec->length < hh)
			spec->length = hh;
		if (*f == 'h' && *(f + 1) != 'h' && spec->length < h)
			spec->length = h;
		if (*f == 'L' && spec->length < L)
			spec->length = L;
		f++;
	}
	return (f);
}

const char	*read_conv_spec(const char *f, t_spec *spec)
{
	if (\
			*f != 'd' &&*f != 'i' && *f != 'o' && *f != 'u' && *f != 'x'\
			&& *f !='X' && *f != 'f' && *f != 'c' && *f != 's'	&& *f != 'p'\
			&& *f != '%'\
		)
		return (0);
	spec->conv = *f;
	return (++f);
}

/*
**	Read all arguments of conversion spceification
**	Return 
**	-pointer to first char after the end of conversion specification
**	-0 in case of any problems (abscence of conversion specifier)
**	Side effects: change a spec
*/

const char	*read_spec(const char *format, t_spec *spec)
{
	init_spec(spec);
	format = read_flags(format, spec);
	format = read_width(format, spec);
	if (*format == '.')
		format = read_precision(++format, spec);
	format = read_length(format, spec);
	format = read_conv_spec(format, spec); 
	return (format);
}
