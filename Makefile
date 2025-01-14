CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBREADLINE = -lreadline
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I./includes -I/opt/homebrew/opt/readline/include
SRC =  srcs/main.c \
	   srcs/prompt/user_prompt.c \
	   srcs/error/error.c \
	   srcs/execution/execution_monitor.c \
	   srcs/execution/execution_command.c \
	   srcs/command/get_path.c \
	   srcs/command/initialise_command.c \
	   srcs/redirection/redirection_monitor.c \
	   srcs/redirection/redirection.c \
	   srcs/redirection/redirection_heredoc.c \
	   srcs/builtin/pwd.c \
	   srcs/builtin/echo.c \
	   srcs/builtin/exit.c \
	   srcs/builtin/cd.c \
	   srcs/builtin/export.c \
	   srcs/builtin/unset.c \
	   srcs/utils/utils.c \
	   srcs/utils/clean.c \
	   srcs/builtin/env.c \
	   srcs/builtin/clear.c \
	   srcs/parser/parser.c \
	   srcs/parser/redirect_lexer.c \
	   srcs/parser/redirects.c \
	   srcs/parser/lexer.c \
	   srcs/parser/lexer_utils.c \
	   srcs/parser/ast_utils.c \
	   srcs/parser/token_utils.c \
	   srcs/parser/debug.c \
	   srcs/parser/expansion/expander.c \
	   srcs/parser/expansion/expander_utils.c \
	   srcs/parser/expansion/wildcard.c \
	   srcs/parser/expansion/wildcard_utils.c \
	   srcs/parser/expansion/env_utils.c \
	   srcs/parser/expansion/dollar_sign.c \
	   srcs/monitor/tree_monitor.c \
	   srcs/monitor/pipe_monitor.c \
	   srcs/monitor/and_or_monitor.c \
	   srcs/monitor/command_monitor.c \
	   srcs/monitor/parenthesis_monitor.c \
	   srcs/env/env_utils.c \
	   srcs/signal/signal.c \
	   srcs/minishell.c \


OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(LIBREADLINE) -L/opt/homebrew/opt/readline/lib

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

