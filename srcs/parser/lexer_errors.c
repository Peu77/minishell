/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:57:44 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 14:14:45 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_redirect_parse_error(t_list *tokens)
{
	int		exit_code;
	t_list	*redirects;
	char	*tmp;
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == TOKEN_STRING)
		{
			redirects = NULL;
			tmp = filter_and_get_redirects(token->value, &redirects,
					&exit_code);
			gc_list_clear(&redirects, free_redirect);
			gc_free_ptr(tmp);
			if (exit_code != 0)
				return (exit_code);
		}
		tokens = tokens->next;
	}
	return (0);
}

static bool	check_parentheses_count(t_list **tokens)
{
	int		open;
	int		close;
	t_list	*tmp;

	tmp = *tokens;
	open = 0;
	close = 0;
	while (tmp)
	{
		if (((t_token *)(tmp)->content)->type == TOKEN_PARENTHESES_OPEN)
			open++;
		if (((t_token *)(tmp)->content)->type == TOKEN_PARENTHESES_CLOSE)
			close++;
		tmp = tmp->next;
	}
	return (open == close);
}

bool	get_lexer_results(t_list **tokens, bool in_quote)
{
	int	redirect_error;

	if (in_quote)
	{
		return (pe("parse error near '\\n'"), gc_list_clear(tokens, free_token),
			false);
	}
	if (!check_parentheses_count(tokens))
	{
		get_shell()->exit_status = 2;
		return (pe("parse error, the parentheses don't match"),
			gc_list_clear(tokens, free_token), false);
	}
	redirect_error = get_redirect_parse_error(*tokens);
	if (redirect_error != 0)
	{
		get_shell()->exit_status = redirect_error;
		return (pe("parse error, each redirect should have an filename"),
			gc_list_clear(tokens, free_token), false);
	}
	return (true);
}
