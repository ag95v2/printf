
#include "printf.h"

/*
**	If we understand rules of C language correctly, :-) this conversions 
**  do not lead to data corruption.
*/

void	*int_extractor(t_spec spec, va_list *vl)
{
	long long	*p;
	
	if (p = ft_memalloc(sizeof(long long)))
	{
		if (spec.length == ll)
			*p += va_arg(*vl, long long);
		else if (spec.length == l)
			*p += va_arg(*vl, long);
		else
			*p += va_arg(*vl, int);
	}
	return ((void *)p);
}

void	*float_extractor(t_spec spec, va_list *vl)
{
	long double	*p;
	
	if (p = ft_memalloc(sizeof(long double)))
	{
		if (spec.length == ll || spec.length == l || spec.length == L)
			*p += va_arg(*vl, long long);
		else
			*p += va_arg(*vl, double);
	}
	return ((void *)p);
}

void	*char_extractor(t_spec spec, va_list *vl)
{
	char	*p;
	
	if (p = ft_memalloc(sizeof(char) * 2))
	{
		p[0] = va_arg(*vl, int);
		p[1] = 0;
	}
	return ((void *)p);
}

/*
**  Single case where we do not allocate external memory
*/

void	*str_extractor(t_spec spec, va_list *vl)
{
	return ((void *)va_arg(*vl, char *));
}
