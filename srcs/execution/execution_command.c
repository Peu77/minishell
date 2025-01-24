/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:33:51 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 00:43:33 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_child_process(t_command *command, char **env_cpy)
{
	command_signals();
	if (execve(command->path, command->argv, env_cpy) == -1)
		command_not_found(command->path);
	destroy_minishell(EXIT_FAILURE);
}

static int	wait_for_process(pid_t pid, char **env_cpy)
{
	int	status;
	int	sig_num;

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

int	execution_command(t_command *command)
{
	pid_t	pid;
	char	**env_cpy;

	if (check_t_shell() != 0)
		return (130);
	env_cpy = copy_env_to_string_array();
	if (!env_cpy)
	{
		pec(ERROR_MALLOC);
		return (1);
	}

	pid = fork();
	reset_signals();
	if (pid == -1)
		return (pec(ERROR_FORK));
	if (pid == 0)
		handle_child_process(command, env_cpy);
	return (wait_for_process(pid, env_cpy));
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
			return (gc_free_ptr(*output_str), pec(ERROR_MALLOC));
		new_str = gc_add(ft_strjoin(temp, command->argument));
		gc_free_ptr(temp);
		if (!new_str)
			return (gc_free_ptr(*output_str), pec(ERROR_MALLOC));
		gc_free_ptr(*output_str);
		*output_str = new_str;
	}
	return (0);
}

int	prepare_execution_command(t_command *command)
{
	int		result;

	if (!command->argv)
		return (pec(ERROR_SPLIT));
	result = execution_command(command);
	return (result);
}
