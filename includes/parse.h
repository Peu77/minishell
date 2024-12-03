/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:36:00 by eebert            #+#    #+#             */
/*   Updated: 2024/12/03 14:03:04 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
#include "libft.h"

typedef enum e_token_type
{
    TOKEN_NONE = -1,
    TOKEN_STRING = 0,
    TOKEN_PIPE = 1,
    TOKEN_SEMICOLON = 2,
    TOKEN_REDIRECT_INPUT = 3,
    TOKEN_REDIRECT_OUTPUT = 4,
    TOKEN_PARENTHESES_OPEN = 5,
    TOKEN_PARENTHESES_CLOSE = 6,
    TOKEN_END = 7,
    TOKEN_AND = 8,
    TOKEN_OR = 9,
    TOKEN_REDIRECT_APPEND = 10,
} t_token_type;

typedef struct s_redirect
{
    int fd_left;
    int fd_right;
    char *file;
} t_redirect;

typedef struct e_token
{
    char *value;
    void *data;
    t_token_type type;
} t_token;

typedef enum e_ast_type {
    AST_COMMAND,
    AST_PIPE,
    AST_SEMICOLON,
    AST_REDIRECT_INPUT,
    AST_REDIRECT_OUTPUT,
    AST_PARENTHESES,
    AST_AND,
    AST_OR,
    AST_REDIRECT_APPEND,
    AST_STRING
} t_ast_type;

typedef struct s_ast_node
{
    char *value;
    t_ast_type type;
    void *data;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;

t_ast_node *parse(char *input);

void lex_tokens(char *input, t_list** tokens);

#endif