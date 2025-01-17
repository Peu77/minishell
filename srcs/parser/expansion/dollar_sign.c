/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:26:36 by eebert            #+#    #+#             */
/*   Updated: 2025/01/15 17:47:44 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_question_mark(int *i, t_list **result_chars)
{
	char	*value;
	t_list	*new_node;

	value = ft_itoa(*update_exit_status());
	if (!value)
		return (pe("malloc failed"), false);
	new_node = ft_lstnew(value);
	if (!new_node)
		return (free(value), ft_lstclear(result_chars, free),
			pe("malloc failed"), false);
	ft_lstadd_back(result_chars, new_node);
	*i += 1;
	return (true);
}

static bool	add_value_as_node(t_list **result_chars, char *value, int *i,
		int end)
{
	char	*value_copy;
	t_list	*new_node;

	value_copy = NULL;
	if (value)
		value_copy = ft_strdup(value);
	else
		value_copy = ft_strdup("");
	if (!value_copy)
		return (pe(ERROR_MALLOC), false);
	new_node = ft_lstnew(value_copy);
	if (!new_node)
		return (free(value_copy), pe(ERROR_MALLOC), false);
	ft_lstadd_back(result_chars, new_node);
	*get_char_count() += ft_strlen(new_node->content);
	*i = end;
	return (true);
}

bool	handle_dollar_sign(const char *str, int *i, t_list **result_chars)
{
	int		start;
	int		end;
	char	*sub_str;

	if (str[*i] == '?')
		return (handle_question_mark(i, result_chars));
	start = *i;
	end = *i;
	while (str[end] && ft_isalnum(str[end]))
		end++;
	sub_str = ft_substr(str, start, end - start);
	if (!sub_str)
		return (pe("malloc failed"), false);
	return (add_value_as_node(result_chars, get_env_value(sub_str), i, end));
}
