/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:29 by eebert            #+#    #+#             */
/*   Updated: 2024/11/30 16:41:36 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

static t_token_type get_token_type(char* c)
{
    if(*c == '|')
        return TOKEN_PIPE;
    if(*c == ';')
        return TOKEN_SEMICOLON;
    if(ft_strncmp(c, "&&", 2) == 0)
        return TOKEN_AND;
    if(ft_strncmp(c, "||", 2) == 0)
        return TOKEN_OR;
    if(*c == '<')
        return TOKEN_REDIRECT_INPUT;
    if(*c == '>')
        return TOKEN_REDIRECT_OUTPUT;
    if(ft_strncmp(c, ">>", 2) == 0)
        return TOKEN_REDIRECT_APPEND;
    if(*c == '(')
        return TOKEN_PARENTHESES_OPEN;
    if(*c == ')')
        return TOKEN_PARENTHESES_CLOSE;
    if(*c == '\0')
        return TOKEN_END;
}