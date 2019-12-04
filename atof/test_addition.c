
#include <stdio.h>
#include "ft_fp.h"

int main(int argc, char **argv)
{
	t_decimal	a, b;
	char		s[80];

	positive_ascii_to(&a, argv[1]);
	to_ascii(a, s);
	printf("a = %s\n", s);

	positive_ascii_to(&b, argv[2]);
	to_ascii(b, s);
	printf("b = %s\n", s);

	add_positive_decimal(&a, &b);
	to_ascii(a, s);
	printf("a + b = %s\n", s);

	return (0);
}
