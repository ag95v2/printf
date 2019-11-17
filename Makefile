SRC := arg_extractors.c \
	   conv_other.c \
	   conv_wrappers_other.c \
	   find_action.c \
	   printf.c \
	   read_spec.c  \
	   printf.h	\
	   read_spec.h \
	   conv_int.c \
	   conv_wrappers_int.c \
	   ftoa.c
all:
	make -C libft
	gcc -g $(SRC) -Wall -Wextra -c -I . -I libft/includes -L libft -lft
	ar rc libftprintf.a *.o ./libft/*.o

clean:
	rm -f *.o

fclean: clean
	rm -f libftprintf.a

re:	fclean all
