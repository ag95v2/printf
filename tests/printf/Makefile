P_ROOT := ../../
SRC := arg_extractors.c \
	   conv_other.c \
	   conv_wrappers_other.c \
	   find_action.c \
	   printf.c \
	   read_spec.c  \
	   printf.h	\
	   read_spec.h \
	   conv_int.c \
	   conv_wrappers_int.c
SRC		:= $(addprefix $(P_ROOT)/,$(SRC))
all:
	make -C ../../libft
	gcc -o test -g $(SRC) main.c -I ../../ -I ../../libft/includes -L ../../libft -lft
