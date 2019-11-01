
#include "printf.h"
#include "libft.h"

/*
**	Fill all fields of structure with zeros.
*/

void		init_spec(t_spec spec)
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

/*
**	Print all normal chars until % or '\0'
**	Return: 
**	-pointer to first '%' if string contains '%' 
**	-0 otherwise
*/

const char	*print_until_percent(const char *format)
{
	while (*format && *format != '%')
		ft_putchar(*(format++));
	return (*format ? format : 0);
}

void read_flag(const char c, t_spec spec)
{
	if (*f == '+')
		spec->flag_plus = 1;
	if (*f == '-')
		spec->flag_dash = 1;
	if (*f == ' ')
		spec->flag_space = 1;
	if (*f == '#')
		spec->flag_hash = 1;
	if (*f == '0')
		spec->flag_zero = 1;
}

/*
**	Read any nonnegative number of flags.
**	One flag can be mentioned more than once
**  No other chars expected here.
**	Return a pointer to first non-flag char in f
*/

const char	*read_flags(const char *f, t_spec spec)
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
const char	*read_width(const char *f, t_spec spec)
{
	if (ft_isdigit(*f))
		spec->width = ft_atoi(*f);
	while (ft_isdigit(*(f++)))
		;
	return (f);
}

/*
**	Skip all digits if they exist in format spec.
**  Fill the field "precision"
**	Return: ptr to first non-digit in f
*/
const char	*read_precision(const char *f, t_spec spec)
{
	if (ft_isdigit(*f))
		spec->precision = ft_atoi(*f);
	while (ft_isdigit(*(f++)))
		;
	return (f);
}


/*
**	Skip all digits if they exist in format spec.
**  Fill the field "precision"
**	Return: ptr to first non-digit in f
*/

const char	*read_length(const char *f, t_spec spec)
{
	if (*f == 'l' && *(f + 1) == 'l')
	{
		spec->length = ll;
		return (f + 2);
	}
	if (*f == 'l' && *(f + 1) != 'l')
	{
		spec->length = l;
		return (f + 1);
	}
	if (*f == 'h' && *(f + 1) == 'h')
	{
		spec->length = hh;
		return (f + 2);
	}
	if (*f == 'h' && *(f + 1) != 'h')
	{
		spec->length = h;
		return (f + 1);
	}
	if (*f == 'L')
	{
		spec->length = L;
		return (f + 1);
	}
	return (f);
}

const char	read_conv_spec(const char *f, t_spec spec)
{
	if (*f != 'd' &&*f != 'i' && *f != 'o' && *f != 'u' && *f != 'x'\
			&& *f !='X' && *f != 'f')
		return (-1);
	if (*f == 'd')
		spec->conv_spec = *f;
	return (++f);
}

/*
**	Read all arguments of conversion spceification
**	Return 
**	-pointer to first char after the end of conversion specification
**	-0 in case of any problems
*/

const char	*read_spec(const char *format, t_spec spec)
{
	format = read_flags(format, spec);
	format = read_width(format, spec);
	if (*format == '.')
		format = read_precision(++format, spec);
	format = read_length(format, spec);
	format = read_conv_spec(format, spec); 
	return (format);
}

int			ft_printf(const char *format, ...)
{
	va_list vl;
	t_spec	spec;
	char	*s;

	va_start(vl, format); 
	while ((format = print_until_percent(format))) 
	{
		if (*(++format) == '%') 
		{
			ft_putchar(*(format++));
			continue;
		}
		format = read_spec(format, spec);
		if (format == -1)
			return (-1);
		s = get_arg_str(spec, va_arg(vl, ))
	}
	
	va_end(vl);
}
