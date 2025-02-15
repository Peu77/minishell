/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:23:59 by eebert            #+#    #+#             */
/*   Updated: 2025/01/29 21:35:54 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "gcollector.h"
# include "libft.h"
# include "parse.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef BANNER
#  define BANNER ""
# endif

# define MAX_VAR_LEN 131072

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

# define MAX_PATH 1024
# define NUM_BUILTINS 8

# define ERROR_GET_LINE "ERROR WITH GETTING THE LINE"
# define ERROR_SPLIT "ERROR WITH SPLIT FUNCTION"
# define ERROR_INITIALISE "ERROR WITH INITIALISING COMMAND"
# define ERROR_NODE "ERROR CREATING THE NODE"
# define ERROR_MALLOC "ERROR ALLOCATION MEMORY"
# define ERROR_FIND_ENV "ERROR FINDING PATH ENV"
# define ERROR_EXECVE "ERROR EXECVE FAILED (COMMAND NOT FOUND)"
# define ERROR_HEREDOC "ERROR OPENING TEMPORARY HEREDOC"
# define ERROR_HEREDOC_SIGNAL "EXITING HEREDOC"
# define ERROR_TOO_ARGUMENT "ERROR TOO MUCH ARGUMENT"
# define ERROR_DIGIT_ARGUMENT "ERROR ARGUMENT IS NOT DIGIT"
# define ERROR_SET_ARGUMENT "ERROR : COMMAND SHOULD BE ./minishell 'commande'"
# define ERROR_PATH "ERROR WITH GETTING PATH"
# define ERROR_FORK "ERROR FORK FAILED"
# define ERROR_OPEN_FILE "ERROR OPEN FILE"

// real command
# define ERROR_PWD "pwd : too many arguments"
# define ERROR_EXPORT "inconsistant type for assignement"

extern char				**environ;

typedef struct s_pipe_data
{
	int					pipe_fds[2];
	pid_t				left_pid;
	pid_t				right_pid;
	int					right_status;
	int					right_result;
}						t_pipe_data;

typedef struct s_command_test
{
	char				*path;
	char				*argument;
	char				*command_name;
	char				*heredoc_filename;
	t_list				*redirect;
	int					saved_stdout;
	int					saved_stdin;
	char				**argv;
}						t_command;

typedef struct s_env_entry
{
	char				*key;
	char				*value;
}						t_env_entry;

typedef struct s_parenthesis_fd
{
	int					fd_backup_stdout;
	int					fd_backup_stdin;
}						t_parenthesis_fd;

typedef struct s_shell
{
	char				*path;
	t_list				*env;
	int					has_parenthesis;
	t_parenthesis_fd	parenthese_fd;
	int					exit_status;
	bool				should_exit;
	int					heredoc_failed;

}						t_shell;

// main

// minishell
void					minishell_non_interactive_argument(char **args,
							int argc);
void					minishell_non_interactive(void);
void					minishell_interactive(void);
void					destroy_minishell(int status);

// monitor
int						tree_monitor(t_ast_node *node, t_command *command);
int						pipe_monitor(t_ast_node *node);
int						and_monitor(t_ast_node *node, t_command *command);
int						or_monitor(t_ast_node *node, t_command *command);
int						command_monitor(t_ast_node *node, t_command *command);
bool					traverse_heredocs(t_ast_node *node);
int						parentheses_monitor(t_ast_node *node,
							t_command *command);
int						semicolon_monitor(t_ast_node *node, t_command *command);

// command
void					get_command_from_node(t_command **command);
void					print_command(t_command *command);
int						concatenate_arguments(char **arg, char **result);
int						transform_node_to_command(char **argv,
							t_command **command, t_list *redirection,
							char *heredoc_filename);
int						get_path(t_command **command);
int						get_redirection(t_command **command,
							t_list *redirection);

// error
int						pe(const char *message);
int						pec(const char *message);
void					pev(const char *message);
int						print_error(const char *message);

t_shell					*get_shell(void);
void					send_greeting(void);

// env utils
void					print_env_list(const bool filter_empty);
bool					is_valid_identifier(const char *identifier);
bool					initialise_env(char **env);
bool					set_env_value(const char *key, const char *value);
bool					add_env_entry(const char *key, const char *value);
void					free_env_entry(void *content);
char					**copy_env_to_string_array(void);
t_env_entry				*get_env_entry(const char *key);
bool					add_env_pairstr(const char *pair_str);

// prompt
int						get_user_prompt_value(char **result);
char					*create_prompt(void);

// builtin
int						ft_pwd(t_command *command);
int						ft_echo(t_command *command, bool is_n);
int						ft_exit(t_command *command);
int						ft_cd(t_command *command);
int						ft_env(t_command *command);
int						ft_export(t_command *command);
int						ft_unset(t_command *command);
int						ft_clear(void);

// execution
int						execution_monitor(t_command *command);
int						prepare_execution_command(t_command *command);
int						execution_command(t_command *command);
void					redirect_input_from_heredoc(const char *filename);

// redirection
bool					redirection_monitor(t_command *command);
bool					redirection_output(t_redirect *redirect);
bool					redirection_input(t_redirect *redirect);
bool					redirection_append(t_redirect *redirect);
bool					redirection_heredoc(const char *delimiter,
							t_ast_node *node);

// heredoc utils
void					convert_pointer_to_string(char *str, void *ptr);

// signal
void					sighandler(int sig);
void					main_signals(void);
void					reset_signals(void);

// signal command
void					command_signals(void);

// signal heredoc
void					signal_heredoc(void);

// utils
int						check_t_shell(void);
void					command_not_found(char *path);
long					ft_atol(const char *str);
char					*ft_strndup(const char *src, size_t len);
void					update_path(void);
char					*join_str_array(char **list, int size);

// clean
void					free_command(t_command **command);
void					free_string_array(char **str_list);
void					free_env_list(void);
void					free_string_array_at_index(char **str_list, int index);
void					split_env_pairstr(const char *pair_str, char *key,
							char *value);

// parser
void					print_ast_node(t_ast_node *node, int depth);
void					print_command_test(t_command *command);

char					*get_env_value(const char *key);

char					*ft_strncpy(char *dest, const char *src, size_t n);

void					restore_parentheses_fd(
							t_parenthesis_fd *parenthesis_fd);

void					reset_terminal_settings(void);
void					disable_ctrl_c_echo(void);

#endif
