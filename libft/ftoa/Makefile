NAME =  ftoa.o

define SRC 
ftoa.c decimal_arithmetic.c

endef

$(NAME):
	@echo "Compiling Ftoa files"
	@gcc -g -Wall -Wextra -Werror -I . -c $(SRC) 

all: $(NAME)

clean:
	@rm -f ft*.o

fclean: clean

re: fclean all