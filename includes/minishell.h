/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:12:19 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 12:29:35 by ftapponn         ###   ########.fr       */
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
#define NUM_BUILTINS 7

#define ERROR_GET_LINE "ERROR WITH GETTING THE LINE"
#define ERROR_SPLIT "ERROR WITH SPLIT FUNCTION"
#define ERROR_INITIALISE "ERROR WITH INITIALISING COMMAND"
#define ERROR_NODE "ERROR CREATING THE NODE"
#define ERROR_MALLOC "ERROR ALLOCATION MEMORY" 
#define ERROR_FIND_ENV "ERROR FINDING PATH ENV"
#define ERROR_PATH "ERROR WITH FINDING PATH"
#define ERROR_EXECVE "ERROR EXECVE FAILED"
#define ERROR_HEREDOC "ERROR OPENING TEMPORARY HEREDOC"
#define ERROR_HEREDOC_SIGNAL "EXITING HEREDOC"
#define ERROR_TOO_ARGUMENT "ERROR TOO MUCH ARGUMENT"
#define ERROR_DIGIT_ARGUMENT "ERROR ARGUMENT IS NOT DIGIT"
#define ERROR_SET_ARGUMENT "ERROR : COMMAND SHOULD BE ./minishell 'commande'"


extern int g_last_exit_status;

typedef struct s_export
{
    char **args;
    char *equal_sign;
	int result;
    int i;
    char *variable_name;
    char *variable_value;
} t_export;

typedef struct s_pipe_data
{
    int pipe_fds[2];
    pid_t left_pid;
    pid_t right_pid;
    int right_status;
    int right_result;
} t_pipe_data;


typedef struct s_env
{
	char *variable_name;
	char *variable_value;
	struct s_env *next;
	struct s_env *previous;
} t_env;

typedef struct s_command_test
{
	char *path;
	char *argument;
	char *command_name;
	t_list *redirect;
	t_env *env;
	int saved_stdout;
	int saved_stdin;
} t_command_test;


// main
void print_env_list(t_env *env_list);

//minishell
void minishell_non_interactive_argument(t_env *env, char *line);
void minishell_non_interactive(t_env *env);
void minishell_interactive(t_env *env);

//monitor 
int tree_monitor(t_ast_node *node, t_command_test *command, t_env *env);
int pipe_monitor(t_ast_node *node, t_env *env);
int and_monitor(t_ast_node *node, t_command_test *command, t_env *env);
int or_monitor(t_ast_node *node, t_command_test *command, t_env *env);
int command_monitor(t_ast_node *node, t_command_test *command,t_env *env);

//command
void get_command_from_node(t_command_test **command);
void print_command(t_command_test *command);
int concatenate_arguments(char **arg, char **result);
int transform_node_to_command(char *value, t_command_test **command, t_list *redirection, t_env *env);
int get_path(t_command_test **command);
int get_redirection(t_command_test **command, t_list *redirection);

//error
int pe(const char *message);
int pec(const char *message);
void pev(const char *message);

//env
t_env *initialise_env(char **env);
//env utils
int unset_variable(t_env *env, const char *var_name);
void print_env_list(t_env *env_list);

//prompt
int get_user_prompt(char **result, t_env *env);

// builtin
int pwd(void);
int echo(t_command_test *command, bool is_n);
int exit_command(t_command_test *command);
int cd(t_command_test *command);
int env(t_command_test *command);
int export_command(t_command_test *command);
int unset(t_command_test *command);


//execution
int execution_monitor(t_command_test *command);
int prepare_execution_command(t_command_test *command);
int execution_command(char **arguments, char *path);

//redirection
void redirection_monitor(t_command_test *command);
void redirection_output(t_redirect *redirect);
void redirection_input(t_redirect *redirect);
void redirection_append(t_redirect *redirect);
void redirection_heredoc(const char *delimiter);

//pipe_monitor

//signal 
void sighandler(int sig);
void main_signals(void);
void heredoc_sighandler(int sig);

//utils
void remove_newline(char *buffer);
long ft_atol(const char *str);
char *ft_strndup(const char *src, size_t len);

//clean
void free_command(t_command_test **command);
void free_command_split(char **command_split);
int free_export_command(t_export *export_list);
void free_env_list(t_env *env);


//parser
void print_ast_node(t_ast_node *node, int depth);
#endif
