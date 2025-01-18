/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:33 by eebert            #+#    #+#             */
/*   Updated: 2025/01/18 23:35:40 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_array(char **str_list)
{
	int	i;

	i = -1;
	if (!str_list)
		return ;
	while (str_list[++i])
		free(str_list[i]);
	if (*str_list)
		free(str_list);
}

void	free_string_array_at_index(char **str_list, int index)
{
	while (index >= 0)
	{
		free(str_list[index]);
		index--;
	}
	free(str_list);
}

static void	free_command_strings(t_command *command)
{
	if (command->path)
	{
		free(command->path);
		command->path = NULL;
	}
	if (command->command_name)
	{
		free(command->command_name);
		command->command_name = NULL;
	}
	if (command->argument)
	{
		free(command->argument);
		command->argument = NULL;
	}
}

static void	close_command_fds(t_command *command)
{
	if (command->saved_stdout > 0)
	{
		close(command->saved_stdout);
		command->saved_stdout = 0;
	}
	if (command->saved_stdin > 0)
	{
		close(command->saved_stdin);
		command->saved_stdin = 0;
	}
}

void	free_command(t_command **command)
{
	if (!command || !*command)
		return ;
	free_string_array((*command)->argv);
	free_command_strings(*command);
	if ((*command)->redirect)
	{
		ft_lstclear(&(*command)->redirect, free_redirect);
		(*command)->redirect = NULL;
	}
	close_command_fds(*command);
	free(*command);
	*command = NULL;
}
