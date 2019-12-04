
#include "printf.h"
#include <stdio.h>

#include <float.h>

int main()
{
	char	*s;
	char	c;
	long double d;

	ft_printf("%.0Lf\n", LDBL_MIN);

	s = &c;
	printf("%.10Lf\n", 0.87650894255l);
	ft_printf("%.10Lf\n", 0.87650894255l);
	
	d = 111111111111111111111111.0l;
	printf("\n\n");
	printf("%Lf\n", d);
	ft_printf("%Lf\n", d);

	ft_printf("%.0Lf\n", LDBL_MIN);
	return (0);
}
