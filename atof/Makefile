SRC = decimal_arithmetic.c

all: clean test_ascii_conv test_positive_addition test_positive_multiplication test_positive_power test_ftoa

test_ftoa:
	gcc -g -o test_ftoa $(SRC) ftoa.c test_ftoa.c -I . -ggdb

test_positive_power:
	gcc -g -o test_positive_power $(SRC) test_power.c -I . -ggdb

test_positive_multiplication:
	gcc -g -o test_positive_multiplication $(SRC) test_multiplication.c -I . -ggdb

test_positive_addition:
	gcc -g -o test_positive_addition $(SRC) test_addition.c -I . -ggdb

test_ascii_conv:
	gcc -g -o test_ascii $(SRC) test_ascii_to.c -I . -ggdb

clean:
	rm -f test_ascii test_positive_addition test_positive_multiplication test_positive_power test_ftoa
