#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "parse.h"
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

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

typedef struct s_command_test
{
	char **envp;
	char *path;
	char *argument;
	char *command_name;
	char *fd_redirection;
	int saved_stdout;
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


typedef struct s_pipe
{
    bool should_exit;
    int pid_signal;
    int pipe_current_process;
    int number_pipe;
    int number_command;
    int (*pipe_fd)[2];
    int parent_pipe_fd[2];
    int pipe_redirection[2];
    int saved_stdout;
} t_pipe;

// main
//monitor 
int tree_monitor(t_ast_node *node, t_command_test *command, char **envp);
void get_command_from_node(t_command_test **command);
void print_command(t_command_test *command);
int concatenate_arguments(char **arg, char **result);
int transform_node_to_command(char *value, t_command_test **command, t_redirect *redirection, char **envp);
int get_path(t_command_test **command);
int get_redirection(t_command_test **command, t_redirect *redirection);

//error
int pe(const char *message);
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
//parser


//pipe 
void create_pipes(t_pipe *pip);
void close_unused_pipes(t_pipe *pip);
void create_parent_pipe(t_pipe *pip);
void prepare_execution(t_pipe *pipe, t_command *command, int i);
void close_all_fds(t_pipe *pipe);


//pipe monitor
int pipe_monitor(t_pipe *pipe, t_command *command, char *user_prompt);

//pipe utils
void add_node_back(t_command **head, t_command *new_node);
t_command *create_node(char *command_str, char **envp);
void print_command_list(t_command *command_list);

//initialiser
int initialise_pipe(t_pipe **pipe, char *user_prompt);
int initialise_monitor(t_pipe **pipe, t_command **command, char *user_prompt, char **envp);
int initialise_command(t_command **command, char *user_prompt, char **envp);

//redirection
void redirection_monitor(t_command *command, t_pipe *pipe);
void redirection_output(t_command_test *command);
void redirection_input(t_command *command, t_pipe *pipe);
void redirection_append(t_command *command, t_pipe *pipe);
void redirection_heredoc(const char *str);

//signal 
void signal_waiting(void);

//utils
void exit_shell(t_pipe *pipe, int erxno);
void remove_newline(char *buffer);
void free_command(t_command_test **command);
void free_pipe(t_pipe **pipe);
void free_command_split(char **command_split);
int free_all(t_pipe **pipe, t_command **command);


//parser
void print_ast_node(t_ast_node *node, int depth);
#endif
