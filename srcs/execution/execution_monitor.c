/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_monitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 18:10:11 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_standard_fds(t_command_test *command)
{
	if (command->saved_stdout != -1)
	{
		if (dup2(command->saved_stdout, STDOUT_FILENO) == -1)
		{
			pev("dup2 failed for restoring STDOUT");
			exit(EXIT_FAILURE);
		}
		close(command->saved_stdout);
	}
	if (command->saved_stdin != -1)
	{
		if (dup2(command->saved_stdin, STDIN_FILENO) == -1)
		{
			pev("dup2 failed for restoring STDIN");
			exit(EXIT_FAILURE);
		}
		close(command->saved_stdin);
	}
}

int	execution_monitor(t_command_test *command)
{
	char	*list_builtin[NUM_BUILTINS] = {"cd", "echo", "env", "exit",
			"export", "pwd", "unset", "clear"};
	int		i;
	int		result;

	i = -1;
	result = 0;
	if (command->redirect)
		redirection_monitor(command);
	while (++i < NUM_BUILTINS)
	{
		if (ft_strncmp(command->command_name, list_builtin[i],
				ft_strlen(list_builtin[i]) + 1) == 0)
		{
			if (i == 0)
				result = ft_cd(command);
			else if (i == 1)
				result = ft_echo(command, 0);
			else if (i == 2)
				result = ft_env(command);
			else if (i == 3)
				result = ft_exit(command);
			else if (i == 4)
				result = ft_export(command);
			else if (i == 5)
				result = ft_pwd(command);
			else if (i == 6)
				result = ft_unset(command);
			else if (i == 7)
				result = ft_clear();
			if (command->saved_stdout)
				restore_standard_fds(command);
			free_command(&command);
			g_last_exit_status = result;
			return (result);
		}
	}
	result = prepare_execution_command(command);
	if (command->saved_stdout)
		restore_standard_fds(command);
	g_last_exit_status = result;
	free_command(&command);
	return (result);
}
