/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:26:36 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 15:36:48 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_question_mark(int *i, t_list **result_chars)
{
	char	*value;
	t_list	*new_node;

	value = gc_add(ft_itoa(get_shell()->exit_status));
	new_node = gc_add(ft_lstnew(value));
	ft_lstadd_back(result_chars, new_node);
	*get_char_count() += ft_strlen(new_node->content);
	*i += 1;
	return (true);
}

static char	*escape_env_value(const char *value)
{
	size_t	i;
	size_t	len;
	size_t	new_len;
	char	*escaped_value;
	size_t	j;

	len = strlen(value);
	new_len = len;
	i = -1;
	while (++i < len)
	{
		if (value[i] == '<' || value[i] == '>')
			new_len++;
	}
	escaped_value = gc_add(ft_calloc(new_len + 1, sizeof(char)));
	j = 0;
	i = -1;
	while (++i < len)
	{
		if (value[i] == '<' || value[i] == '>')
			escaped_value[j++] = '\\';
		escaped_value[j++] = value[i];
	}
	escaped_value[j] = '\0';
	return (escaped_value);
}

static bool	add_value_as_node(t_list **result_chars, char *value, int *i,
		int end)
{
	char	*value_copy;
	t_list	*new_node;

	value_copy = NULL;
	if (value)
		value_copy = escape_env_value(value);
	else
		value_copy = gc_add(ft_strdup(""));
	new_node = gc_add(ft_lstnew(value_copy));
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
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	sub_str = gc_add(ft_substr(str, start, end - start));
	return (add_value_as_node(result_chars, get_env_value(sub_str), i, end));
}
