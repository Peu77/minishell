/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:39 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 20:23:14 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execution_command(char **arguments, char *path)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return pec(ERROR_FORK);
	if (pid == 0)
	{
		if (!path)
			exit(print_error(ERROR_FOUND_COMMAND));
		if (execve(path, arguments, NULL) == -1)
			exit(pec(ERROR_EXECVE));
	}
	else
	{
		waitpid(pid, &status, 0);
		exit_status = WEXITSTATUS(status);
		return (exit_status);
	}
	return (1);
}

int	prepare_execution_command(t_command_test *command)
{
	char	*str;
	char	**arguments;
	char	*temp;
	int		result;
	char	*new_str;

	str = ft_strdup(command->command_name);
	if (!str)
		return (pec(ERROR_MALLOC));
	if (command->argument != NULL)
	{
		temp = ft_strjoin(str, " ");
		if (!temp)
		{
			free(str);
			return (pec(ERROR_MALLOC));
		}
		new_str = ft_strjoin(temp, command->argument);
		free(temp);
		if (!new_str)
		{
			free(str);
			return (pec(ERROR_MALLOC));
		}
		free(str);
		str = new_str;
	}
	arguments = ft_split(str, ' ');
	if (!arguments)
	{
		free(str);
		return (pec(ERROR_SPLIT));
	}
	result = execution_command(arguments, command->path);
	free_command_split(arguments);
	free(str);
	return (result);
}
