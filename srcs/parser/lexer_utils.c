/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:58:20 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 16:08:26 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gcollector.h>
#include <parse.h>
#include <stdio.h>

t_token_type	is_redirect(const char *str, size_t i)
{
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\\')
		return (TOKEN_NONE);
	if (ft_strncmp(str + i, "<<", 2) == 0)
		return (TOKEN_REDIRECT_INPUT_APPEND);
	if (ft_strncmp(str + i, ">>", 2) == 0)
		return (TOKEN_REDIRECT_APPEND);
	if (*(str + i) == '<')
		return (TOKEN_REDIRECT_INPUT);
	if (*(str + i) == '>')
		return (TOKEN_REDIRECT_OUTPUT);
	return (TOKEN_NONE);
}

t_token_type	get_token_type(const char *str, size_t i, bool in_quote)
{
	if (in_quote)
		return (TOKEN_STRING);
	if (is_escaped(str, i))
		return (TOKEN_STRING);
	if (ft_strncmp(str + i, "&&", 2) == 0)
		return (TOKEN_AND);
	if (ft_strncmp(str + i, "||", 2) == 0)
		return (TOKEN_OR);
	if (str[i] == '|')
		return (TOKEN_PIPE);
	if (str[i] == ';')
		return (TOKEN_SEMICOLON);
	if (str[i] == '(')
		return (TOKEN_PARENTHESES_OPEN);
	if (str[i] == ')')
		return (TOKEN_PARENTHESES_CLOSE);
	if (str[i] == ';')
		return (TOKEN_SEMICOLON);
	if (str[i] == '\0')
		return (TOKEN_END);
	return (TOKEN_STRING);
}

bool	add_token(t_list **tokens, t_token_type type, char *value)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = create_token(type, value, NULL);
	new_node = gc_add(ft_lstnew(new_token));
	ft_lstadd_back(tokens, new_node);
	return (true);
}
