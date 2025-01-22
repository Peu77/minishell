/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:36 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 21:17:30 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	handle_tilde_expansion(int *i, t_list **result_chars)
{
	t_list	*new_node;
	char	*home;
	char	*str_cpy;

	home = get_env_value("HOME");
	if (!home)
		return (true);
	str_cpy = gc_add(ft_strdup(home));
	new_node = gc_add(ft_lstnew(str_cpy));
	(*get_char_count()) += ft_strlen(str_cpy);
	(*i)++;
	return (ft_lstadd_back(result_chars, new_node), true);
}
