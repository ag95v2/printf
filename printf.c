#include "printf.h"
#include "read_spec.h"


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

/*
**	Determine type of next arg according to spec
**	Extract argument from original vl
**	Return its string representation 
*/

char		*get_arg_str(t_spec spec, va_list *vl)
{
	void		*arg;
	char		*res;
	t_conv_f	*action;

	// TODO: process possible malloc errors here
	action = find_action(spec);
	arg = action->arg_extract(spec, vl);
	res = action->to_str(arg);
	if (action->cleanup_needed)
		free(arg);
	return (res);
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
			// TODO: we would prefer buffered output.
			ft_putchar(*(format++));
			continue;
		}
		format = read_spec(format, &spec);
		if (!format)
			return (-1);
		s = get_arg_str(spec, &vl);
		ft_putstr(s);
	}
	// TODO: process case with multiple string args without format string
	va_end(vl);
	return (0);
}
