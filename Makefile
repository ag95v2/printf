# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpenney <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/29 14:53:58 by dpenney           #+#    #+#              #
#    Updated: 2019/12/05 06:29:34 by bgian            ###   ########.fr        #
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
	   apply_spec6.c \

OBJ = $(SRC:.c = o)

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc -c $(SRC) -Wall -Wextra  -I . -I libft/includes -I libft/ftoat
	@ar rc libftprintf.a *.o ./libft/*.o ./libft/ftoa/*.o
	@ranlib $(NAME)
	@echo "\n\n\n	It's done! Use it  ( • )( • ) ԅ(‾⌣‾ԅ)  \n\n\n"

clean:
	@rm -f *.o
	@rm -f ./libft/*.o
	@rm -f ./libft/ftoa/*.o
	@rm -f *.gch

fclean: clean
	@rm -f libftprintf.a
	@rm -f ./libft/libft.a

re: fclean all
