#include "printf.h"

char	*w_ftoa(void *x)
{
	return (ftoa(*(long double *)x));
}

char	*w_ctoa(void *x)
{
	return (ctoa(*(char *)x));
}

char	*w_stoa(void *x)
{
	return (stoa((char *)x));
}

char	*w_ptoa(void *x)
{
	return (ptoa(x));
}
