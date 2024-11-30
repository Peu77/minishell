/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:36:00 by eebert            #+#    #+#             */
/*   Updated: 2024/11/30 16:41:08 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_ast_node
{
    char *value;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;

typedef enum e_token_type
{
    TOKEN_STRING,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_REDIRECT_INPUT,
    TOKEN_REDIRECT_OUTPUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_PARENTHESES_OPEN,
    TOKEN_PARENTHESES_CLOSE,
    TOKEN_END
} t_token_type;

t_ast_node *parse(char *input);

#endif