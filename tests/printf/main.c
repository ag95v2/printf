
#include "printf.h"
#include <stdio.h>

int main()
{
	char *s;

	s = NULL;
	printf("%-16.1s\n", s);
	ft_printf("%-16.1s\n", s);

	/*
	ft_printf("\nUsing normal functions (already implemented)\n");
	ft_printf("Test1 (no format string)\n");
	ft_printf("Test2 (char): %c\n", 'c');
	ft_printf("Test3 (str): %s\n", "Some string!");
	ft_printf("Test4 (multiple args): arg1:%s arg2:%s\n", "hello", "world");
	ft_printf("\nUsing stub functions (yet not implemented)\n");
	ft_printf("Test4 (integer): %i\n", 123);
	ft_printf("Test5 (decimal): %d\n", 123123);
	ft_printf("Test6 (float): %f\n", 123.45);
	ft_printf("Test6.1 (float): %f\n", 1123213.456);
	ft_printf("Test7 (hex): %x\n", 123);
	ft_printf("Test7.1 (hex): %x\n", 1);
	ft_printf("Test8 (HEX): %X\n", 123);
	ft_printf("Test9 (octal): %o\n", 9);
	ft_printf("Test10 (pointer): %p\n", 123);
	*/
	return (0);
}
