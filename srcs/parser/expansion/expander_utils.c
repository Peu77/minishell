/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:36 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 16:55:11 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*get_char_count(void)
{
	static int	char_count = 0;

	return (&char_count);
}

bool	handle_tilde_expansion(int *i, t_list **result_chars)
{
	t_list	*new_node;
	char	*home;
	char	*str_cpy;

	home = get_env_value("HOME");
	if (!home)
		return (true);
	str_cpy = ft_strdup(home);
	if (!str_cpy)
		return (pe(ERROR_MALLOC), false);
	new_node = ft_lstnew(str_cpy);
	if (!new_node)
		return (pe(ERROR_MALLOC), false);
	(*get_char_count()) += ft_strlen(str_cpy);
	(*i)++;
	return (ft_lstadd_back(result_chars, new_node), true);
}

bool	add_char_to_result(const char *str, int *i, t_list **result_chars)
{
	char	*str_cpy;
	t_list	*new_node;

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
