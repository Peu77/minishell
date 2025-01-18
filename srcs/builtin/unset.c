/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:34:50 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 16:19:51 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:49 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:51:03 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_variable_from_env(const char *key)
{
	const size_t	key_len = ft_strlen(key);
	t_list			*current;
	t_list			*previous;
	t_env_entry		*entry;

	previous = NULL;
	current = get_shell()->env;
	while (current)
	{
		entry = current->content;
		if (ft_strncmp(entry->key, key, key_len) == 0)
		{
			if (current == get_shell()->env)
				get_shell()->env = current->next;
			else
				previous->next = current->next;
			free_env_entry(entry);
			free(current);
			return (true);
		}
		previous = current;
		current = current->next;
	}
	return (false);
}

int	ft_unset(t_command *command)
{
	char	**arg;
	int		result;

	if (!command->argument)
		return (pev("unset: not enough arguments"), 1);
	arg = ft_split(command->argument, ' ');
	result = 0;
	while (*arg)
	{
		if (!remove_variable_from_env(*arg))
			result = -1;
		arg++;
	}
	return (free_string_array(arg), result);
}
