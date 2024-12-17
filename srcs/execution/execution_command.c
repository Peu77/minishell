/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:39 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/17 14:17:50 by ftapponn         ###   ########.fr       */
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
		return (pec(ERROR_FORK));
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

int	build_command_string(t_command_test *command, char **output_str)
{
	char	*temp;
	char	*new_str;

	*output_str = ft_strdup(command->command_name);
	if (!(*output_str))
		return (pec(ERROR_MALLOC));
	if (command->argument != NULL && *command->argument != '\0')
	{
		temp = ft_strjoin(*output_str, " ");
		if (!temp)
			return (free(*output_str), pec(ERROR_MALLOC));
		new_str = ft_strjoin(temp, command->argument);
		free(temp);
		if (!new_str)
			return (free(*output_str), pec(ERROR_MALLOC));
		free(*output_str);
		*output_str = new_str;
	}
	return (0);
}

int	prepare_execution_command(t_command_test *command)
{
	char	*str;
	char	**arguments;
	int		result;

	if (build_command_string(command, &str) != 0)
		return (pec(ERROR_MALLOC));
	arguments = ft_split(str, ' ');
	free(str);
	if (!arguments)
		return (pec(ERROR_SPLIT));
	result = execution_command(arguments, command->path);
	free_command_split(arguments);
	return (result);
}
