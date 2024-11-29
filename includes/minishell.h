#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdio.h>

#define RED     "\033[1;31m"
#define RESET   "\033[0m"
// main

//error
void pe(const char *message);

//prompt
void get_user_prompt(char **result);

// builtin

//env

//execution

//parser

//pipe

//redirection

#endif
