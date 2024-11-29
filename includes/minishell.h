#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdio.h>

#define RED     "\033[1;31m"
#define RESET   "\033[0m"
#define MAX_PATH 1024
#define ERROR_GET_LINE "ERROR WITH GETTING THE LINE"
#define NUM_BUILTINS 7

// main

//error
int pe(const char *message);

//prompt
int get_user_prompt(char **result);

// builtin
int pwd(void);
//env

//execution
void execution_monitor(char *user_prompt);
void execution_command(char *user_prompt);
//parser

//pipe
void pipe_monitor(char *user_prompt);

//redirection

#endif
