/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_monitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 17:20:57 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void restore_standard_fds(t_command_test *command)
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

int execution_monitor(t_command_test *command, t_env *env_list)
{
	char *list_builtin[NUM_BUILTINS] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
	int i = -1;
	int result = 0;

	if (command->redirect)
		redirection_monitor(command);
	while (++i < NUM_BUILTINS)
	{
		if (ft_strncmp(command->command_name, list_builtin[i], ft_strlen(list_builtin[i]) + 1) == 0)
		{
			if (i == 0)
				result = cd(command);
			else if (i == 1)
				result = echo(command, 0);
			else if (i == 2)
				result = env(command, env_list);
			else if (i == 3)
				result = exit_command(command);
			else if (i == 4)
				result = export_command(command, env_list);
			else if (i == 5)
				result = pwd();
			else if (i == 6)
				result = unset(command, env_list);
			if (command->saved_stdout)
				restore_standard_fds(command);
			g_last_exit_status = result;
			return (result);
		}
	}
	result = prepare_execution_command(command);
	if (command->saved_stdout)
		restore_standard_fds(command);
	g_last_exit_status = result;
	return (result);
}
