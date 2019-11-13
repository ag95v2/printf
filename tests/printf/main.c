
#include "printf.h"
#include <stdio.h>

//Mix tests
static unsigned int		mx_u = 235;
static long double			mx_Lf = 0.375l;
static double				mx_f = 0.625;
static long				mx_li =  4223372036854775800;
static long long			mx_lli = 3223372036654775200;
static char				mx_c = 'G';
static short				mx_hi = -3244;
static char				mx_hhi = 'F';
static char			   *mx_s = "Hello, World!";
static int					mx_i = 42;

int main()
{
	printf("%p    %i    %li    %lli    %s  \n",
	    	&mx_i, mx_i, mx_li, mx_lli, mx_s);
	fflush(stdout);

	ft_printf("%p    %i    %li    %lli    %s  ",
	    	&mx_i, mx_i, mx_li, mx_lli, mx_s);

	printf("  %Lf    %p    %i    %li    %lli    %s  \n",
	    		mx_Lf, &mx_i, mx_i, mx_li, mx_lli, mx_s);
	fflush(stdout);

	ft_printf("  %Lf    %p    %i    %li    %lli    %s  ",
	    		mx_Lf, &mx_i, mx_i, mx_li, mx_lli, mx_s);

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
