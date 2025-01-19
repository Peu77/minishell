/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:36:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 17:31:02 by ftapponn         ###   ########.fr       */
/*   Updated: 2025/01/19 16:58:08 by eebert           ###   ########.fr       */
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
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	exit(127);
}

int	execution_command(char **arguments, char *path)
{
	pid_t	pid;
	int		sig_num;
	int		status;
	char	**env_cpy;

	env_cpy = copy_env_to_string_array();
	if (!env_cpy)
		return (pec(ERROR_MALLOC), 1);
	pid = fork();
	reset_signals();
	if (pid == -1)
		return (pec(ERROR_FORK));
	if (pid == 0)
	{
		signal_command();
		if (execve(path, arguments, env_cpy) == -1)
			command_not_found(path);
		exit(EXIT_SUCCESS);
	}
		waitpid(pid, &status, 0);
		free_string_array(env_cpy);
		main_signals();
		if (WIFSIGNALED(status))
		{
			sig_num = WTERMSIG(status);
			return (128 + sig_num);
		}
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
	int		result;

	if (build_command_string(command, &str) != 0)
		return (pec(ERROR_MALLOC));
	free(str);
	if (!command->argv)
		return (pec(ERROR_SPLIT));
	result = execution_command(command->argv, command->path);
	return (result);
}
