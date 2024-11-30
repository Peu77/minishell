/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:36:00 by eebert            #+#    #+#             */
/*   Updated: 2024/11/30 17:20:33 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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

typedef struct s_ast_node
{
    char *value;
    t_token_type type;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;

t_ast_node *parse(char *input);

#endif