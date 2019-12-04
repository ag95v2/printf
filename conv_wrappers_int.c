
#include "printf.h"

char	*w_itoa_b10u(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b10u(*(long long *)n));
}

char	*w_itoa_b10(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b10(*(long long *)n));
}

char	*w_itoa_b2(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b2(*(long long *)n));
}

char	*w_itoa_b8(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b8(*(long long *)n));
}

char	*w_itoa_X(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_bX(*(long long *)n));
}

char	*w_itoa_x(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_bx(*(long long *)n));
}
