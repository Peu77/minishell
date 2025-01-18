/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:58:20 by eebert            #+#    #+#             */
/*   Updated: 2025/01/18 23:51:55 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_token_type	is_redirect(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if(str[i] == '\\')
		return TOKEN_NONE;
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
	if(is_escaped(str, i))
		return (TOKEN_STRING);
	if (ft_strncmp(str + i, "&&", 2) == 0)
		return (TOKEN_AND);
	if (ft_strncmp(str + i, "||", 2) == 0)
		return (TOKEN_OR);
	if (str[i] == '|')
		return (TOKEN_PIPE);
	if (str[i]== ';')
		return (TOKEN_SEMICOLON);
	if (str[i] == '(')
		return (TOKEN_PARENTHESES_OPEN);
	if (str[i] == ')')
		return (TOKEN_PARENTHESES_CLOSE);
	if (str[i] == '\0')
		return (TOKEN_END);
	return (TOKEN_STRING);
}

bool	add_token(t_list **tokens, t_token_type type, char *value)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = create_token(type, value, NULL);
	if (!new_token)
		return (false);
	new_node = ft_lstnew(new_token);
	if (!new_node)
		return (free(new_token), false);
	ft_lstadd_back(tokens, new_node);
	return (true);
}
