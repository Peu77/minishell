CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I./includes
SRC =  srcs/main.c \
	   srcs/prompt/user_prompt.c \
	   srcs/error/error.c \
	   srcs/pipe/pipe_monitor.c \
	   srcs/pipe/pipe_utils.c \
	   srcs/initialiser/initialiser_monitor.c \
	   srcs/execution/execution_monitor.c \
	   srcs/execution/execution_command.c \
	   srcs/redirection/redirection_monitor.c \
	   srcs/redirection/redirection.c \
	   srcs/builtin/pwd.c \
	   srcs/builtin/echo.c \
	   srcs/builtin/exit.c \
	   srcs/builtin/cd.c \
	   srcs/builtin/export.c \
	   srcs/builtin/unset.c \
	   srcs/utils/utils.c \
	   srcs/builtin/env.c \
	   srcs/signal/signal.c \
	   srcs/parser/parser.c \
	   srcs/parser/redirects.c \
	   srcs/parser/lexer.c \
	   srcs/parser/ast_utils.c \
	   srcs/parser/token_utils.c \


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

