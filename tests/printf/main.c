
#include "printf.h"
#include <stdio.h>
#include <float.h>

int main()
{
	char	*s;
	char	c;
	long double d;
	short	x;
	int		y;

	d = 1.42;
	d = 1.42l;

	
	//ft_printf("{%Lf}\n", 1.42l);
	//printf("{%Lf}\n", 1.42l);

	ft_printf("{%f}{%lf}{%Lf}\n", 1.42, 1.42, 1.42l);
	printf("{%f}{%lf}{%Lf}\n", 1.42, 1.42, 1.42l);
	x =  32768;
	y = 32768;

	ft_printf("%hd\n", 32768);
	printf("%hd\n", 32768);

	ft_printf("%hhd\n", 128);
	printf("%hhd\n", 128);

	ft_printf("%hhd\n", -129);
	printf("%hhd\n", -129);

	printf("%.3c\n", 'a');
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
