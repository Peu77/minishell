#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdio.h>

#define RED     "\033[1;31m"
#define RESET   "\033[0m"
// main

//error
int pe(const char *message);

//prompt
int get_user_prompt(char **result);

// builtin

//env

//execution

//parser

//pipe

//redirection

#endif
