#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdio.h>

#define RED     "\033[1;31m"
#define RESET   "\033[0m"
#define MAX_PATH 1024
#define ERROR_GET_LINE "ERROR WITH GETTING THE LINE"
#define NUM_BUILTINS 7

typedef struct s_command
{
	char *path;
	char *argument;
	char *command_name;
	struct s_command *next;
	struct s_command *previous;
} t_command;

typedef struct s_pipe
{
	int pipe_current_process;
	int number_pipe;
	int number_command;
	int (*pipe_fd)[2];
	int parent_pipe_fd[2];
} t_pipe;
// main

//error
int pe(const char *message);

//prompt
int get_user_prompt(char **result);

// builtin
char *pwd(void);
//env

//execution
void execution_monitor(t_command *command);
void execution_command(t_command *command);
void execute_two_pipes(t_command *cmd1, t_command *cmd2);
//parser

//pipe
void pipe_monitor(char *user_prompt);

//pipe initialising
void initialise_pipe(t_pipe **pipe, t_command **command, char *user_prompt);

//pipe utils
void add_node_back(t_command **head, t_command *new_node);
t_command *create_node(char *command_str);
void print_command_list(t_command *command_list);
int count_pipe(char *str);

//redirection

#endif
