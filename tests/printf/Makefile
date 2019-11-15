P_ROOT := ../../
all:
	make -C $(P_ROOT)libft
	make -C $(P_ROOT)
	gcc -o test -g main.c -I $(P_ROOT) -I $(P_ROOT)libft/includes -L $(P_ROOT)libft -lft -L $(P_ROOT) -lftprintf
