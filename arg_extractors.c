
#include "printf.h"
#include "fp_type.h"

int		is_usgn(t_spec spec)
{
	if (\
			spec.conv == 'u' ||\
			spec.conv == 'o' ||\
			spec.conv == 'x' ||\
			spec.conv == 'X'\
		)
		return (1);
	return (0);
}

void	*extr_sint(t_spec spec, va_list *vl, long long *p)
{
		if (spec.length == ll)
			*p += va_arg(*vl, long long);
		else if (spec.length == l)
			*p += va_arg(*vl, long);
		else
			*p += va_arg(*vl, int);
		return ((void *)p);
}

void	*extr_uint(t_spec spec, va_list *vl, long long *p)
{
		if (spec.length == ll)
			*p += va_arg(*vl, unsigned long long);
		else if (spec.length == l)
			*p += va_arg(*vl, unsigned long);
		else
			*p += va_arg(*vl, unsigned int);
		return ((void *)p);
}

/*
**	Choose integer extractor depending on signed/unsigned
*/

i_extr_fun	choose_i_extr(t_spec spec)
{
	return (is_usgn(spec) ? &extr_uint : &extr_sint);
}

/*
**	If we understand rules of C language correctly, :-) this conversions 
**  do not lead to data corruption.
**	Now we may have UB (signed overflow).
*/

void	*int_extractor(t_spec spec, va_list *vl)
{
	long long	*p;

	if ((p = ft_memalloc(sizeof(long long))))
		return (choose_i_extr(spec)(spec, vl, p));
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
	char *arg;

	arg = va_arg(*vl, char *);	
	// UB reproduction (small precision and NULL str)
	if (!arg && spec.precision > 0 && spec.precision < 6)
		arg = "";
	if (!arg)
		arg = "(null)";
	return ((void *)arg);
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
