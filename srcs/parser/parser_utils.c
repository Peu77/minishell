/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:38:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 23:33:06 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO: expand and parse redirects
static bool	handle_token_string(t_token *token, t_list **tokens, t_list** redirects)
{
	char	*trimmed;
	char*	tmp;
	int redirect_exit_code;

	tmp = expand_string(token->value);
	if(!tmp)
		return (false);
	gc_free_ptr(token->value);
	token->value = tmp;
	tmp = filter_and_get_redirects(token->value, redirects, &redirect_exit_code);
	if (!tmp) {
		return (false);
	}
	ft_unescape_string(tmp);
	trimmed = ft_strtrim(tmp, " ");
	if (ft_strlen(trimmed) != 0)
		return (printf("parse error near `%s'\n", trimmed), gc_free_ptr(trimmed),
			false);
	gc_free_ptr(trimmed);
	*tokens = (*tokens)->next;
	return (true);
}

/**
 * future: set token_string value to parentheses node and before execute expandit and filter redirects from it
 * @param tokens
 * @param parentheses_node
 * @return
 */
bool parse_redirects_for_parenteses(t_list **tokens,
                                    t_ast_node *parentheses_node)
{
	while (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN_STRING)
	{
			if (!handle_token_string((*tokens)->content, tokens, &parentheses_node->redirects))
				return (NULL);
	}
	return (true);
}

bool	is_empty_string_token(t_token *token)
{
	int	i;

	if (token->type != TOKEN_STRING)
		return (false);
	if (token->value == NULL || ft_strlen(token->value) == 0)
		return (true);
	i = 0;
	while (token->value[i])
	{
		if (!ft_isspace(token->value[i]))
			return (false);
		i++;
	}
	return (true);
}
