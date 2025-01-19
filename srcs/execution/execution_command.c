/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:33:51 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 19:56:00 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:36:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 18:21:09 by ftapponn         ###   ########.fr       */
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
/*   Updated: 2025/01/19 17:31:02 by ftapponn         ###   ########.fr       */
/*   Updated: 2025/01/19 17:33:01 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

static void	command_not_found(char *path)
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
	if (errno == EACCES || errno == EISDIR)
		destroy_minishell(126);
	destroy_minishell(127);
}

int	execution_command(t_command* command)
{
	t_shell *shell = get_shell();
	if (shell->heredoc_failed == 1)
	{
		shell->heredoc_failed = 0;
		return (130);
	}
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
