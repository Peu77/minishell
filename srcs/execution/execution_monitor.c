/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_monitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:56:26 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 15:10:03 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	initialise_builtin(char *list_builtin[NUM_BUILTINS])
{
	list_builtin[0] = "cd";
	list_builtin[1] = "echo";
	list_builtin[2] = "env";
	list_builtin[3] = "exit";
	list_builtin[4] = "export";
	list_builtin[5] = "pwd";
	list_builtin[6] = "unset";
	list_builtin[7] = "clear";
}

void	restore_standard_fds(t_command *command)
{
	if (command->saved_stdout != -1)
	{
		if (dup2(command->saved_stdout, STDOUT_FILENO) == -1)
		{
			pev("dup2 failed for restoring STDOUT");
		}
		close(command->saved_stdout);
	}
	if (command->saved_stdin != -1)
	{
		if (dup2(command->saved_stdin, STDIN_FILENO) == -1)
		{
			pev("dup2 failed for restoring STDIN");
		}
		close(command->saved_stdin);
	}
}

int	execute_builtin(t_command *command, int builtin_index)
{
	int	result;

	result = 0;
	if (builtin_index == 0)
		result = ft_cd(command);
	else if (builtin_index == 1)
		result = ft_echo(command, 0);
	else if (builtin_index == 2)
		result = ft_env(command);
	else if (builtin_index == 3)
		result = ft_exit(command);
	else if (builtin_index == 4)
		result = ft_export(command);
	else if (builtin_index == 5)
		result = ft_pwd(command);
	else if (builtin_index == 6)
		result = ft_unset(command);
	else if (builtin_index == 7)
		result = ft_clear();
	if (command->saved_stdout)
		restore_standard_fds(command);
	free_command(&command);
	return (result);
}

int	execution_monitor(t_command *command)
{
	char	*list_builtin[NUM_BUILTINS];
	int		i;
	int		result;

	initialise_builtin(list_builtin);
	i = -1;
	result = 0;
	if (command->redirect)
		if(!redirection_monitor(command, NULL)) {
			get_shell()->exit_status = 1;
			return 1;
		}
	while (++i < NUM_BUILTINS)
	{
		if (ft_strncmp(command->command_name, list_builtin[i],
				ft_strlen(list_builtin[i]) + 1) == 0)
		{
			result = execute_builtin(command, i);
			get_shell()->exit_status = result;
			return (result);
		}
	}
	result = prepare_execution_command(command);
	if (command->saved_stdout)
		restore_standard_fds(command);
	get_shell()->exit_status = result;
	return (free_command(&command), result);
}
