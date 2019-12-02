#include <stdio.h>
#include <stdlib.h>
#include "ft_fp.h"

int main(int argc, char **argv)
{
	t_decimal	a;
	int			power;
	char		s[80];

	positive_ascii_to(&a, argv[1]);
	to_ascii(a, s);
	printf("a = %s\n", s);

	power = atoi(argv[2]);
	printf("b = %d\n", power);

	power_positive_decimal(&a, power);
	to_ascii(a, s);
	printf("a ^ b = %s\n", s);

	return (0);
}
