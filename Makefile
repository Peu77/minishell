#vg --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=supp.supp ./minishell
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
	   srcs/terminal.c \
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
	@$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(LIBREADLINE)
	@echo "$(GREEN)$(NAME) compiled successfully!                             $(RESET)"

$(LIBFT):
	$(call loading_animation,make -C $(LIBFT_DIR))
	@cp $(LIBFT_DIR)/libft.h includes/

%.o: %.c
	@$(eval TOTAL := $(words $(SRC)))
	@$(eval PROGRESS := $(shell echo $$(($(PROGRESS)+1))))
	@$(eval PERCENT := $(shell echo $$(($(PROGRESS)*100/$(TOTAL)))))
	@$(call progress_bar,$(PERCENT))
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR);

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR);

re: fclean all

debug: CFLAGS += -g -DDEBUG=1
debug: re


.PHONY: all clean fclean re debug

RED     := $(shell tput setaf 1)
GREEN   := $(shell tput setaf 2)
YELLOW  := $(shell tput setaf 3)
BLUE    := $(shell tput setaf 4)
MAGENTA := $(shell tput setaf 5)
CYAN    := $(shell tput setaf 6)
WHITE   := $(shell tput setaf 7)
RESET   := $(shell tput sgr0)

define progress_bar
	@printf "$(CYAN)["; \
	for i in $(shell seq 1 50); do \
		if [ $$i -le $$(($(1)*50/100)) ]; then \
			printf "$(GREEN)█$(RESET)"; \
		else \
			printf "$(WHITE)░$(RESET)"; \
		fi; \
	done; \
	printf "$(CYAN)] %3d%%$(RESET)\r" $(1);
endef

define loading_animation
	@mkdir -p .build_temp
	@echo '#!/bin/bash\n$(1) > .build_temp/output.log 2>&1' > .build_temp/build.sh
	@chmod +x .build_temp/build.sh
	@printf "$(YELLOW)Building libft$(RESET)"
	@./.build_temp/build.sh & \
	PID=$$!; \
	while kill -0 $$PID 2>/dev/null; do \
		for s in ⣾ ⣽ ⣻ ⢿ ⡿ ⣟ ⣯ ⣷; do \
			printf "$(CYAN)%s$(RESET)\r$(YELLOW)Building libft %s$(RESET)" "$$s" "$$s"; \
			sleep 0.1; \
			if ! kill -0 $$PID 2>/dev/null; then \
				break; \
			fi; \
		done; \
	done; \
	wait $$PID; \
	EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -eq 0 ]; then \
		printf "\r$(GREEN)Libft compiled successfully!$(RESET)\n"; \
	else \
		printf "\r$(RED)Build failed! See error below:$(RESET)\n"; \
		cat .build_temp/output.log; \
	fi; \
	rm -rf .build_temp; \
	exit $$EXIT_CODE
endef
