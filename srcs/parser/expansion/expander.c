/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:00:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/16 21:16:03 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strlst_to_str(t_list *lst)
{
	char	*result;
	int		cpy_offset;

	cpy_offset = 0;
	result = malloc(*get_char_count() + 1);
	if (!result)
		return (pe(ERROR_MALLOC), NULL);
	result[*get_char_count()] = '\0';
	while (lst)
	{
		ft_strlcpy(result + cpy_offset, lst->content, ft_strlen(lst->content)
			+ 1);
		cpy_offset += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (result);
}

static bool	handle_single_quotes(const char *str, int *i, t_list **result_chars)
{
	t_list	*new_node;
	char	*str_cpy;
	size_t	len;

	len = 0;
	(*i)++;
	while (str[*i + len] && str[*i + len] != '\'')
		len++;
	str_cpy = ft_substr(str, *i, len);
	if (!str_cpy)
		return (pe(ERROR_MALLOC), false);
	new_node = ft_lstnew(str_cpy);
	(*get_char_count()) += (int)len;
	*i += len + 1;
	if (!new_node)
		return (pe(ERROR_MALLOC), false);
	ft_lstadd_back(result_chars, new_node);
	return (true);
}

static bool	handle_double_quotes(const char *str, int *i, t_list **result_chars)
{
	t_list	*new_node;

	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$' && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '?'))
		{
			(*i)++;
			if (!handle_dollar_sign(str, i, result_chars))
				return (false);
			continue ;
		}
		new_node = ft_lstnew(ft_substr(str, *i, 1));
		if (!new_node)
			return (pe(ERROR_MALLOC), false);
		(*get_char_count())++;
		ft_lstadd_back(result_chars, new_node);
		(*i)++;
	}
	(*i)++;
	return (true);
}

static bool	handle_non_quotes(const char *str, int *i, t_list **result_chars)
{
	t_list		*new_node;
	char		*str_cpy;
	const int	wildcard_len = get_wildcard_len(str + *i);

	if (wildcard_len > 0)
	{
		if (!expand_wildcard(str + *i, wildcard_len, result_chars))
			return (false);
		*i += wildcard_len;
		return (true);
	}
	if (str[*i] == '$' && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '?'))
	{
		(*i)++;
		return (handle_dollar_sign(str, i, result_chars));
	}
	if(str[*i] == '~' && !handle_tilde_expansion(i, result_chars))
		return (false);
	str_cpy = ft_substr(str, *i, 1);
	if (!str_cpy)
		return (pe(ERROR_MALLOC), false);
	new_node = ft_lstnew(str_cpy);
	if (!new_node)
		return (free(str_cpy), pe(ERROR_MALLOC), false);
	(*get_char_count())++;
	(*i)++;
	return (ft_lstadd_back(result_chars, new_node), true);
}

bool	interpret_command_string(t_ast_node *node)
{
	char	*str;
	int		i;
	t_list	*result_chars;

	*get_char_count() = 0;
	result_chars = NULL;
	i = 0;
	str = node->value;
	if (!str)
		return (true);
	while(str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if ((str[i] == '\'' && !handle_single_quotes(str, &i, &result_chars))
			|| (str[i] == '\"' && !handle_double_quotes(str, &i,
					&result_chars)))
			return (ft_lstclear(&result_chars, free), false);
		if (str[i] == '\'' || str[i] == '\"')
			continue ;
		if (!handle_non_quotes(str, &i, &result_chars))
			return (ft_lstclear(&result_chars, free), false);
	}
	free(node->value);
	node->value = strlst_to_str(result_chars);
	return (ft_lstclear(&result_chars, free), node->value != NULL);
}

/*
int	main(void) {
	t_ast_node node;
	node.type = AST_COMMAND;
	node.value = ft_strdup("echo '$PATH': paaath: \"$gfweio $PATH\"");
	node.redirects = NULL;
	interpret_command_string(&node);
	printf("result: %s\n", node.value);
	free(node.value);
	return (0);
}
*/
