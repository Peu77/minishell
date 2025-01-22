/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:00:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 12:35:58 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_single_quotes(const char *str, int *i, t_list **result_chars)
{
	size_t	len;

	len = 0;

	if(str[*i] == 0)
		return false;
	while (str[*i + len + 1] && (str[*i + len + 1] != '\'' || is_escaped(str, *i + len + 1)))
		len++;

	return (add_str_to_result(str, (size_t*)i, result_chars, len + 2) &&str[*i] != '\0');
}

static bool	handle_double_quotes(const char *str, int *i, t_list **result_chars)
{
	if(!add_str_to_result(str, (size_t*)i, result_chars, 1))
		return false;
	while (str[*i] && (str[*i] != '\"' || is_escaped(str, *i)))
	{
		if (str[*i] == '$' && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '?'))
		{
			(*i)++;
			if (!handle_dollar_sign(str, i, result_chars))
				return (false);
			continue ;
		}
		if(!add_str_to_result(str, (size_t*)i, result_chars, 1))
			return false;
	}
	if(!add_str_to_result(str, (size_t*)i, result_chars, 1))
		return false;
	return (str[*i] != '\0');
}

static bool	handle_non_quotes(const char *str, int *i, t_list **result_chars)
{
	if(str[*i] == 0)
		return false;
	if (str[*i] == '$' && !is_escaped(str, *i) && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '?'))
	{
		(*i)++;
		return (handle_dollar_sign(str, i, result_chars));
	}
	if (str[*i] == '~' && !is_escaped(str, *i) && !((*i > 0 && str[*i -1] == '~') || str[*i + 1] == '~') && !handle_tilde_expansion(i, result_chars))
		return (false);
	return (add_str_to_result(str, (size_t*)i, result_chars, 1));
}

char*			expand_string(const char* str)
{
	int		i;
	t_list	*result_chars;
	const int	len = ft_strlen(str);

	result_chars = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (i < len)
	{
		if ((str[i] == '\'' && !is_escaped(str, i) && !handle_single_quotes(str, &i, &result_chars))
			|| (str[i] == '\"' && !is_escaped(str, i) && !handle_double_quotes(str, &i,
					&result_chars)))
			break;
		if ((str[i] == '\'' || str[i] == '\"') && !is_escaped(str, i))
			continue ;
		if (!handle_non_quotes(str, &i, &result_chars))
			break;
	}
	return (strlst_to_str(result_chars));
}

/*
const int	wildcard_len = get_wildcard_len(str + *i);

	if (wildcard_len > 0)
	{
		if (!expand_wildcard(str + *i, wildcard_len, result_chars))
			return (false);
		*i += wildcard_len;
		return (true);
	}
 */

/*
int	main(void) {
	t_ast_node node;
	node.type = AST_COMMAND;
	node.value = ft_strdup("echo '$PATH': paaath: \"$gfweio $PATH\"");
	node.redirects = NULL;
	interpret_command_string(&node);
	printf("result: %s\n", node.value);
	gc_free_ptr(node.value);
	return (0);
}
*/
