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
#define ERROR_HEREDOC "Erreu opening temporary heredoc"
#define ERROR_HEREDOC_SIGNAL "EXITING HEREDOC"

typedef struct s_command_test
{
	char **envp;
	char *path;
	char *argument;
	char *command_name;
	t_list *redirect;
	int saved_stdout;
	int saved_stdin;
} t_command_test;

typedef struct s_command
{
	char *path;
	char *argument;
	char *command_name;
	char *redirection;
	char **envp;
	char *redirection_token;
	char *delimiter;
	struct s_command *next;
	struct s_command *previous;
} t_command;

typedef struct s_pipe_data
{
    int pipe_fds[2];
    pid_t left_pid;
    pid_t right_pid;
    int right_status;
    int right_result;
} t_pipe_data;


// main
//monitor 
int tree_monitor(t_ast_node *node, t_command_test *command, char **envp);
int pipe_monitor(t_ast_node *node, char **envp);
int and_monitor(t_ast_node *node, t_command_test *command, char **envp);
int or_monitor(t_ast_node *node, t_command_test *command, char **envp);
int command_monitor(t_ast_node *node, t_command_test *command, char **envp);

//command
void get_command_from_node(t_command_test **command);
void print_command(t_command_test *command);
int concatenate_arguments(char **arg, char **result);
int transform_node_to_command(char *value, t_command_test **command, t_list *redirection, char **envp);
int get_path(t_command_test **command);
int get_redirection(t_command_test **command, t_list *redirection);

//error
int pe(const char *message);
int pec(const char *message);
void pev(const char *message);

//prompt
int get_user_prompt(char **result);

// builtin
int pwd(void);
int echo(t_command_test *command, bool is_n);
int exit_command(t_command_test *command);
int cd(t_command_test *command);
int env(t_command_test *command);
int export_command(t_command_test *command);
int unset(t_command_test *command);
//env

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
void signal_waiting(void);

//utils
//void exit_shell(t_pipe *pipe, int erxno);
void remove_newline(char *buffer);
void free_command(t_command_test **command);
//void free_pipe(t_pipe **pipe);
void free_command_split(char **command_split);
//int free_all(t_pipe **pipe, t_command **command);


//parser
void print_ast_node(t_ast_node *node, int depth);
#endif
