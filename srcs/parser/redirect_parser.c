/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:06:47 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 13:05:36 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>


static size_t get_redirect_len(const char *str)
{
	size_t len;

	len = 0;
	while(str[len]){
		if(skip_quotes(str, &len))
			continue;
		if(ft_isspace(str[len]) && (len != 0 && str[len -1] != '\\'))
			break;
		len++;
	}
	return len;
}

static bool	parse_right_area(const char *str, size_t *i, t_redirect *redirect)
{
	size_t	filename_len;
	char** split;

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
	filename_len = get_redirect_len(str + *i);
	if (filename_len == 0)
		return (pe("parse error near `\\n'"), false);
	redirect->file = ft_substr(str, *i, filename_len);
	if (!redirect->file)
		return (false);
	split = split_quotes(redirect->file);
	if (!split)
		return (gc_free_ptr(redirect->file), false);
	gc_free_ptr(redirect->file);
	redirect->file = split[0];
	ft_unescape_string(redirect->file);
	*i += filename_len;
	return (true);
}

bool	parse_redirect(t_list **redirects, const char *str,
		t_token_type redirect_type, size_t *i)
{
	t_redirect	*redirect;
	t_list		*new_node;

	redirect = create_redirect(-1, -1, redirect_type, NULL);
	if (!redirect)
		return (gc_free_ptr(redirect), false);
	if (ft_isdigit(str[*i]))
	{
		redirect->fd_left = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]))
			(*i)++;
	}
	(*i) += 1 + (redirect_type >= TOKEN_REDIRECT_APPEND);
	if (str[*i] == 0 || (str[*i] == '&' && str[*i + 1] == 0))
		return (pe("parse error near `\\n'"), gc_free_ptr(redirect),
			false);
	if (!parse_right_area(str, i, redirect))
		return (free(redirect), false);
	new_node = ft_lstnew(redirect);
	if (!new_node)
		return (free_redirect(redirect), false);
	return (ft_lstadd_back(redirects, new_node), true);
}
