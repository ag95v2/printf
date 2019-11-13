
#include "printf.h"

/*
**	If we understand rules of C language correctly, :-) this conversions 
**  do not lead to data corruption.
*/

void	*int_extractor(t_spec spec, va_list *vl)
{
	long long	*p;
	
	if ((p = ft_memalloc(sizeof(long long))))
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
	
	if ((p = ft_memalloc(sizeof(long double))))
	{
		if (spec.length == ll || spec.length == l || spec.length == L)
			*p += va_arg(*vl, long double);
		else
			*p += va_arg(*vl, double);
	}
	return ((void *)p);
}

void	*char_extractor(t_spec spec, va_list *vl)
{
	char	*p;
	
	(void)spec;
	if ((p = ft_memalloc(sizeof(char) * 2)))
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
	(void)spec;
	return ((void *)va_arg(*vl, char *));
}

/*
**  Do nothing. Really, just do nothing
**  Will be used for % conv specifier
*/

/* 
** Probably, this can break portability to clang.
** Use void() typecasting then (void)spec
** Return value is nonzero and must not be used
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void	*dummy_extractor(t_spec spec, va_list *vl)
{
	return ((void *)1);
}
#pragma GCC diagnostic pop
