#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdio.h>

#define RED     "\033[1;31m"
#define RESET   "\033[0m"
#define MAX_PATH 1024
#define ERROR_GET_LINE "ERROR WITH GETTING THE LINE"

// main

//error
int pe(const char *message);

//prompt
int get_user_prompt(char **result);

// builtin
int pwd(void);
//env

//execution

//parser

//pipe
void pipe_monitor(char *prompt_user);

//redirection

#endif
