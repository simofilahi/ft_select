NAME= ft_select
CC= gcc
FLAGS= -Wextra -Werror -Wall
INC= inc/.
SRCS= *.c
BINS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft/
		$(CC) $(FLAGS) $(SRCS) -L ./libft -lft -ltermcap -o $(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -I $(INC) $< -c -o $@

clean:
			make -C libft/ clean
			rm -f $(OBJ)

fclean: clean
			make -C libft/ fclean
			rm -f $(NAME)

re: fclean all

