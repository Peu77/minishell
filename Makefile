CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBREADLINE = -lreadline
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I./includes
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
	   srcs/redirection/heredoc_utils.c \
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
	   srcs/parser/parser2.c \
	   srcs/parser/parser_utils.c \
	   srcs/parser/redirect_parser.c \
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
	   srcs/parser/expansion/dollar_sign.c \
	   srcs/parser/expansion/spliter.c \
	   srcs/parser/expansion/redirects_filter.c \
	   srcs/parser/expansion/str_builder.c \
	   srcs/parser/expansion/str_escape.c \
	   srcs/parser/expansion/quote_utils.c \
	   srcs/parser/expansion/split_extractor.c \
	   srcs/parser/expansion/split_counter.c \
	   srcs/parser/lexer_errors.c \
	   srcs/monitor/tree_monitor.c \
	   srcs/monitor/pipe_monitor.c \
	   srcs/monitor/logical_monitor.c \
	   srcs/monitor/command_monitor.c \
	   srcs/monitor/parenthesis_monitor.c \
	   srcs/env/env_utils.c \
	   srcs/env/env_utils2.c \
	   srcs/env/env_utils3.c \
	   srcs/gcollector/gcollector.c \
	   srcs/gcollector/gc_list.c \
	   srcs/gcollector/gc_files.c \
	   srcs/utils/str_utils.c \
	   srcs/signal/signal_command.c \
	   srcs/signal/signal_main.c \
	   srcs/signal/signal_heredoc.c \
	   srcs/greeting.c \
	   srcs/minishell.c \
	   srcs/minishell_destroy.c \




OBJ = $(SRC:.c=.o)
NAME = minishell

BANNER =   " ██████   ██████  ███              ███          █████               ████  ████\n"\
           "░░██████ ██████  ░░░              ░░░          ░░███               ░░███ ░░███\n"\
           " ░███░█████░███  ████  ████████   ████   █████  ░███████    ██████  ░███  ░███\n"\
           " ░███░░███ ░███ ░░███ ░░███░░███ ░░███  ███░░   ░███░░███  ███░░███ ░███  ░███\n"\
           " ░███ ░░░  ░███  ░███  ░███ ░███  ░███ ░░█████  ░███ ░███ ░███████  ░███  ░███\n"\
           " ░███      ░███  ░███  ░███ ░███  ░███  ░░░░███ ░███ ░███ ░███░░░   ░███  ░███\n"\
           " █████     █████ █████ ████ █████ █████ ██████  ████ █████░░██████  █████ █████\n"\
           "░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░\n"




CFLAGS += -DBANNER='$(BANNER)'

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(LIBREADLINE)

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

debug: CFLAGS += -g -DDEBUG=1
debug: re


.PHONY: all clean fclean re

