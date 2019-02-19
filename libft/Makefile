
NAME = libft.a
SRCS = *.c 
FLAGS = -Wextra -Werror -Wall  
HEADERS = libft.h
OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : 
	gcc -c $(FLAGS) $(SRCS) -I .
	ar rc $(NAME) $(OBJ)

clean : 
	rm -f $(OBJ)

fclean : clean 
	rm -f $(NAME)

re : fclean all
