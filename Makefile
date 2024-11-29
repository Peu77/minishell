CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I./includes
SRC =  srcs/main.c srcs/prompt/user_prompt.c srcs/error/error.c srcs/pipe/pipe_monitor.c

OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.h includes/

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR);

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR);


re: fclean all

.PHONY: all clean fclean re

