/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:34:50 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 13:27:33 by ftapponn         ###   ########.fr       */
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
			gc_free_ptr(current);
			return (true);
		}
		previous = current;
		current = current->next;
	}
	return (false);
}

int	ft_unset(t_command *command)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while (command->argv[i])
	{
		if (!is_valid_identifier(command->argv[i]))
		{
			write(STDERR_FILENO, RED, ft_strlen(RED));
			write(STDERR_FILENO, "minishell: unset: `", 20);
			write(STDERR_FILENO, command->argv[i], ft_strlen(command->argv[i]));
			write(STDERR_FILENO, "': not a valid identifier", 26);
			write(STDERR_FILENO, RESET, ft_strlen(RESET));
			write(STDERR_FILENO, "\n", 1);
			result = 1;
		}
		remove_variable_from_env(command->argv[i]);
		i++;
	}
	return (result);
}
