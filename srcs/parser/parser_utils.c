/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:38:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 20:10:44 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	handle_token_string(t_token *token, t_list **tokens)
{
	char	*trimmed;

	trimmed = ft_strtrim(token->value, " ");
	if (ft_strlen(trimmed) != 0)
		return (printf("parse error near `%s'\n", trimmed), free(trimmed),
			false);
	free(trimmed);
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
	t_token		*token;
	t_redirect	*redirect;
	t_list		*new_node;

	while (*tokens && (is_redirect_token(((t_token *)(*tokens)->content)->type)
		|| ((t_token *)(*tokens)->content)->type == TOKEN_STRING))
	{
		token = (*tokens)->content;
		redirect = token->data;
		if (((t_token *)(*tokens)->content)->type == TOKEN_STRING)
		{
			if (!handle_token_string((*tokens)->content, tokens))
				return (NULL);
			continue ;
		}
		new_node = ft_lstnew(redirect);
		token->data = NULL;
		if (!new_node)
			return (free_redirect(redirect), NULL);
		ft_lstadd_back(&parentheses_node->redirects, new_node);
		*tokens = (*tokens)->next;
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
