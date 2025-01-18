/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:36:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/18 18:04:55 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:39 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/13 19:18:54 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

static void	command_not_found(const char *path)
{
	char	*message;

	message = ": command not found";
	while (*path)
	{
		write(STDERR_FILENO, path, 1);
		path++;
	}
	write(STDERR_FILENO, message, 19);
	write(STDERR_FILENO, "\n", 1);
	exit(127);
}

int	execution_command(char **arguments, char *path)
{
	pid_t	pid;
	int		status;
	char	**env_cpy;

	env_cpy = copy_env_to_string_array();
	if (!env_cpy)
		return (pec(ERROR_MALLOC), 1);
	pid = fork();
	if (pid == -1)
		return (pec(ERROR_FORK));
	reset_signals();
	if (pid == 0)
	{
		main_signals();
		if (execve(path, arguments, env_cpy) == -1)
			command_not_found(path);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	free_string_array(env_cpy);
	main_signals();
	return (WEXITSTATUS(status));
}

int	build_command_string(t_command *command, char **output_str)
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

int	prepare_execution_command(t_command *command)
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
	free_string_array(arguments);
	return (result);
}
