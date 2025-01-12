/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:39:38 by eebert            #+#    #+#             */
/*   Updated: 2025/01/12 19:50:38 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:46 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/17 14:55:04 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command_split(char **command_split)
{
	int	i;

	i = -1;
	if (!command_split)
		return ;
	while (command_split[++i])
		free(command_split[i]);
	free(command_split);
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
