/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:35:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/13 13:23:24 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:12:19 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:52:52 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:03 by eebert            #+#    #+#             */
/*   Updated: 2024/12/07 15:25:48 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "parse.h"
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>


#define RED     "\033[1;31m"
#define RESET   "\033[0m"
#define MAX_PATH 1024
#define NUM_BUILTINS 8

#define ERROR_GET_LINE "ERROR WITH GETTING THE LINE"
#define ERROR_SPLIT "ERROR WITH SPLIT FUNCTION"
#define ERROR_INITIALISE "ERROR WITH INITIALISING COMMAND"
#define ERROR_NODE "ERROR CREATING THE NODE"
#define ERROR_MALLOC "ERROR ALLOCATION MEMORY" 
#define ERROR_FIND_ENV "ERROR FINDING PATH ENV"
#define ERROR_EXECVE "ERROR EXECVE FAILED"
#define ERROR_HEREDOC "ERROR OPENING TEMPORARY HEREDOC"
#define ERROR_HEREDOC_SIGNAL "EXITING HEREDOC"
#define ERROR_TOO_ARGUMENT "ERROR TOO MUCH ARGUMENT"
#define ERROR_DIGIT_ARGUMENT "ERROR ARGUMENT IS NOT DIGIT"
#define ERROR_SET_ARGUMENT "ERROR : COMMAND SHOULD BE ./minishell 'commande'"
#define ERROR_PATH "ERROR WITH GETTING PATH"
#define ERROR_FORK "ERROR FORK FAILED"

//real command
#define ERROR_FOUND_COMMAND "zsh: command not found."
#define ERROR_PWD "pwd : too many arguments"
#define ERROR_EXPORT "inconsistant type for assignement"

extern char **environ;

typedef struct s_pipe_data
{
    int pipe_fds[2];
    pid_t left_pid;
    pid_t right_pid;
    int right_status;
    int right_result;
} t_pipe_data;

typedef struct s_command_test
{
	char *path;
	char *argument;
	char *command_name;
	t_list *redirect;
	int saved_stdout;
	int saved_stdin;
} t_command;

typedef struct s_shell {
	char* path;
	char** env;
	int exit_status;
} t_shell;


// main
void print_env_list(char **env);

//minishell
void minishell_non_interactive_argument(char *line);
void minishell_non_interactive();
void minishell_interactive();

//monitor 
int tree_monitor(t_ast_node *node, t_command *command);
int pipe_monitor(t_ast_node *node);
int and_monitor(t_ast_node *node, t_command *command);
int or_monitor(t_ast_node *node, t_command *command);
int command_monitor(t_ast_node *node, t_command *command);
int	parentheses_monitor(t_ast_node *node, t_command *command);


//command
void get_command_from_node(t_command **command);
void print_command(t_command *command);
int concatenate_arguments(char **arg, char **result);
int transform_node_to_command(char *value, t_command **command, t_list *redirection);
int get_path(t_command **command);
int get_redirection(t_command **command, t_list *redirection);

//error
int pe(const char *message);
int pec(const char *message);
void pev(const char *message);
int	print_error(const char *message);

t_shell* get_shell(void);

//env utils
char	*ft_strtok(char *str, const char delim);
void print_env_list(char **env);
int	is_valid_identifier(const char *str);
char **initialise_env(char **env);

//prompt
int get_user_prompt(char **result);

// builtin
int ft_pwd(t_command *command);
int ft_echo(t_command *command, bool is_n);
int ft_exit(t_command *command);
int ft_cd(t_command *command);
int ft_env(t_command *command);
int ft_export(t_command *command);
int ft_unset(t_command *command);
int	ft_clear(void);

//execution
int execution_monitor(t_command *command);
int prepare_execution_command(t_command *command);
int execution_command(char **arguments, char *path);

//redirection
void redirection_monitor(t_command *command);
void redirection_output(t_redirect *redirect);
void redirection_input(t_redirect *redirect);
void redirection_append(t_redirect *redirect);
void redirection_heredoc(const char *delimiter);

//signal 
void sighandler(int sig);
void main_signals(void);
void heredoc_sighandler(int sig);

//utils
void remove_newline(char *buffer);
long ft_atol(const char *str);
char *ft_strndup(const char *src, size_t len);
int *update_exit_status();

//clean
void free_command(t_command **command);
void free_command_split(char **command_split);
void free_env_list();

//parser
void print_ast_node(t_ast_node *node, int depth);
void print_command_test(t_command *command);
#endif
