NAME = philo
SRC = main.c src/utils/utils.c src/utils/input.c src/utils/actions.c src/utils/input_checks.c src/helpers.c src/utils/forks.c src/utils/philos.c src/utils/input_2.c
OBJ = $(SRC:.c=.o)
INC = -Iinc/
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean .c.o