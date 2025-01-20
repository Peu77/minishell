/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:33:51 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 12:14:16 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	execution_command(t_command* command)
{
	pid_t	pid;
	int		sig_num;
	int		status;
	char	**env_cpy;

	if(check_t_shell() != 0)
		return (check_t_shell());
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
		if (execve(command->path, command->argv, env_cpy) == -1)
			command_not_found(command->path);
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

	*output_str = gc_add(ft_strdup(command->command_name));
	if (!(*output_str))
		return (pec(ERROR_MALLOC));
	if (command->argument != NULL && *command->argument != '\0')
	{
		temp = gc_add(ft_strjoin(*output_str, " "));
		if (!temp)
			return (free(*output_str), pec(ERROR_MALLOC));
		new_str = gc_add(ft_strjoin(temp, command->argument));
		gc_free_ptr(temp);
		if (!new_str)
			return (free(*output_str), pec(ERROR_MALLOC));
		gc_free_ptr(*output_str);
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
	gc_free_ptr(str);
	if (!command->argv)
		return (pec(ERROR_SPLIT));
	result = execution_command(command);
	return (result);
}
