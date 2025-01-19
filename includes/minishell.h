/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:22:12 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 18:00:12 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parse.h"
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define MAX_VAR_LEN 131072

# define RED "\033[1;31m"
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
# define ERROR_FOUND_COMMAND "zsh: command not found."
# define ERROR_PWD "pwd : too many arguments"
# define ERROR_EXPORT "inconsistant type for assignement"

extern char	**environ;

typedef struct s_pipe_data
{
	int		pipe_fds[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		right_status;
	int		right_result;
}			t_pipe_data;

typedef struct s_command_test
{
	char	*path;
	char	*argument;
	char	*command_name;
	t_list	*redirect;
	int		saved_stdout;
	int		saved_stdin;
	char**  argv;
}			t_command;

typedef struct s_env_entry
{
	char	*key;
	char	*value;
}			t_env_entry;

typedef struct s_shell
{
	char	*path;
	t_list	*env;
	int		exit_status;
	bool	should_exit;
}			t_shell;

typedef struct s_parenthesis_fd
{
	int		fd_backup_stdout;
	int		fd_backup_stdin;
}			t_parenthesis_fd;

// main

// minishell
int			minishell_non_interactive_argument(char **args, int argc);
void		minishell_non_interactive(void);
void		minishell_interactive(void);

// monitor
int			tree_monitor(t_ast_node *node, t_command *command);
int			pipe_monitor(t_ast_node *node);
int			and_monitor(t_ast_node *node, t_command *command);
int			or_monitor(t_ast_node *node, t_command *command);
int			command_monitor(t_ast_node *node, t_command *command);
int			parentheses_monitor(t_ast_node *node, t_command *command);

// command
void		get_command_from_node(t_command **command);
void		print_command(t_command *command);
int			concatenate_arguments(char **arg, char **result);
int			transform_node_to_command(char **argv, t_command **command,
				t_list *redirection);
int			get_path(t_command **command);
int			get_redirection(t_command **command, t_list *redirection);

// error
int			pe(const char *message);
int			pec(const char *message);
void		pev(const char *message);
int			print_error(const char *message);

t_shell		*get_shell(void);

// env utils
void	print_env_list(const bool filter_empty);
int			is_valid_identifier(const char *str);
bool		initialise_env(char **env);
bool		set_env_value(const char *key, const char *value);
bool		add_env_entry(const char *key, const char *value);
void		free_env_entry(void *content);
char		**copy_env_to_string_array(void);
t_env_entry	*get_env_entry(const char *key);
bool		add_env_pairstr(const char *pair_str);

// prompt
int			get_user_prompt(char **result);

// builtin
int			ft_pwd(t_command *command);
int			ft_echo(t_command *command, bool is_n);
int			ft_exit(t_command *command);
int			ft_cd(t_command *command);
int			ft_env(t_command *command);
int			ft_export(t_command *command);
int			ft_unset(t_command *command);
int			ft_clear(void);

// execution
int			execution_monitor(t_command *command);
int			prepare_execution_command(t_command *command);
int			execution_command(t_command *command);

// redirection
void		redirection_monitor(t_command *command,
				t_parenthesis_fd *parenthesis_fd);
void		redirection_output(t_redirect *redirect);
void		redirection_input(t_redirect *redirect);
void		redirection_append(t_redirect *redirect);
int		redirection_heredoc(const char *delimiter, t_command *command,
				t_parenthesis_fd *parenthesis_fd);

// signal
void		sighandler(int sig);
void		main_signals(void);
void		reset_signals(void);
void		heredoc_sighandler(int sig);
void 		signal_command(void);

// utils
long		ft_atol(const char *str);
char		*ft_strndup(const char *src, size_t len);
void		update_path(void);
char		*join_str_array(char **list, int size);

// clean
void		free_command(t_command **command);
void		free_string_array(char **str_list);
void		free_env_list(void);
void		free_string_array_at_index(char **str_list, int index);
void		split_env_pairstr(const char *pair_str, char *key, char *value);

// parser
void		print_ast_node(t_ast_node *node, int depth);
void		print_command_test(t_command *command);

char		*get_env_value(const char *key);

#endif
