/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:38:33 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 19:54:25 by eebert           ###   ########.fr       */
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
		gc_free_ptr(str_list[i]);
	if (*str_list)
		gc_free_ptr(str_list);
}

void	free_string_array_at_index(char **str_list, int index)
{
	while (index >= 0)
	{
		gc_free_ptr(str_list[index]);
		index--;
	}
	gc_free_ptr(str_list);
}

static void	free_command_strings(t_command *command)
{
	if (command->path)
	{
		gc_free_ptr(command->path);
		command->path = NULL;
	}
	if (command->command_name)
	{
		gc_free_ptr(command->command_name);
		command->command_name = NULL;
	}
	if (command->argument)
	{
		gc_free_ptr(command->argument);
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
		gc_list_clear(&(*command)->redirect, free_redirect);
		(*command)->redirect = NULL;
	}
	close_command_fds(*command);
	gc_free_ptr(*command);
	*command = NULL;
}
