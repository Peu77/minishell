/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:54:07 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 20:48:25 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <minishell.h>
#include <stdbool.h>

void	free_redirect(void *content)
{
	t_redirect	*redirect;

	redirect = content;
	free(redirect->file);
	free(redirect);
}

bool	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_INPUT || type == TOKEN_REDIRECT_OUTPUT
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_REDIRECT_INPUT_APPEND);
}

t_redirect	*create_redirect(int fd_left, int fd_right, t_token_type type,
		char *file)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->fd_left = fd_left;
	redirect->fd_right = fd_right;
	redirect->type = type;
	redirect->file = file;
	return (redirect);
}

/**

* parse all redirects and save them in the redirects l
* ist also skip all the command tokens and return the last token
 * @param redirects
 * @param tokens
 * @return the last token of the redirect/commands section
 */
t_list	*parse_redirects_tokens_to_tree(t_list **redirects, t_list *tokens)
{
	t_list		*new_node;
	t_token		*token;
	t_redirect	*redirect;

	while (tokens && (is_redirect_token(((t_token *)tokens->content)->type)
			|| ((t_token *)tokens->content)->type == TOKEN_STRING))
	{
		token = tokens->content;
		if (token->type != TOKEN_STRING)
		{
			redirect = token->data;
			token->data = NULL;
			new_node = ft_lstnew(redirect);
			if (!new_node)
				return (free_redirect(redirect), NULL);
			ft_lstadd_back(redirects, new_node);
		}
		if (tokens->next == NULL)
			return (tokens);
		tokens = tokens->next;
	}
	return (tokens);
}
