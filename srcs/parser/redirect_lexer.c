/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:06:47 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 16:20:20 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	parse_right_area(const char *str, size_t *i, t_redirect *redirect)
{
	int	filename_len;

	if (str[*i] == '&')
	{
		(*i)++;
		redirect->fd_right = ft_atoi(str + *i);
		while (str[*i] && ft_isdigit(str[*i]))
			(*i)++;
		return (true);
	}
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	filename_len = 0;
	while (str[*i + filename_len] && !ft_isspace(str[*i + filename_len]))
		filename_len++;
	if (filename_len == 0)
		return (pe("parse error near `\\n'"), false);
	redirect->file = ft_substr(str, *i, filename_len);
	if (redirect->file == NULL)
		return (false);
	*i += filename_len;
	return (true);
}

bool	parse_redirect_to_token(t_list **tokens, const char *str,
		t_token_type redirect_type, size_t *i)
{
	t_redirect	*redirect;
	t_token		*token;
	t_list		*new_node;

	redirect = create_redirect(-1, -1, redirect_type, NULL);
	token = create_token(redirect_type, NULL, redirect);
	if (!redirect || !token)
		return (free(redirect), free(token), false);
	if (ft_isdigit(str[*i]))
	{
		redirect->fd_left = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]))
			(*i)++;
	}
	(*i) += 1 + (redirect_type >= TOKEN_REDIRECT_APPEND);
	if (str[*i] == 0 || (str[*i] == '&' && str[*i + 1] == 0))
		return (pe("parse error near `\\n'"), free(redirect), free(token),
			false);
	if (!parse_right_area(str, i, redirect))
		return (free(redirect), free(token), false);
	new_node = ft_lstnew(token);
	if (!new_node)
		return (free_redirect(redirect), free(token), false);
	return (ft_lstadd_back(tokens, new_node), true);
}
