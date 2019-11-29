# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpenney <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/29 14:53:58 by dpenney           #+#    #+#              #
#    Updated: 2019/11/29 14:54:00 by dpenney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC := arg_extractors.c \
	   arg_extractors2.c \
	   conv_other.c \
	   conv_wrappers_other.c \
	   find_action.c \
	   printf.c \
	   read_spec.c \
	   read_spec2.c \
	   printf.h	\
	   read_spec.h \
	   conv_int.c \
	   conv_int2.c \
	   conv_wrappers_int.c \
	   conv_wrappers_int2.c \
	   apply_spec.c \
	   apply_spec2.c \
	   apply_spec3.c \
	   apply_spec4.c \
	   apply_spec5.c \
	   ftoa.c \
	   int_len.c

OBJ = $(SRC:.c = o)

all: $(NAME)

#если необходимо проверить через собственный main, то следует
#добавить -L ./libft

$(NAME):
	@make -C libft
	@gcc -g $(SRC) -Wall -Wextra  -c -I . -I libft/includes -lft  -DMAC_OS
	@ar rc libftprintf.a *.o ./libft/*.o
	@ranlib $(NAME)
	@echo "\n\n\n	It's done! Use it  ( • )( • ) ԅ(‾⌣‾ԅ)  \n\n\n"

clean:
	@rm -f *.o
	@rm -f ./libft/*.o

fclean: clean
	@rm -f libftprintf.a
	@rm -f ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re $(NAME)
