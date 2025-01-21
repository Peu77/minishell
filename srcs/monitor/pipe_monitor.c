/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:23:59 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 16:32:33 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:04 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/19 18:20:49 by ftapponn         ###   ########.fr       */
/*   Created: 2025/01/19 17:33:51 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 18:00:30 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	pipe_left_process(t_ast_node *node, t_pipe_data *pipe_data)
{
	gc_close_fd(pipe_data->pipe_fds[0]);
	dup2(pipe_data->pipe_fds[1], STDOUT_FILENO);
	gc_close_fd(pipe_data->pipe_fds[1]);
	destroy_minishell(tree_monitor(node->left, NULL));
}

void	pipe_right_process(t_ast_node *node, t_pipe_data *pipe_data)
{
	gc_close_fd(pipe_data->pipe_fds[1]);
	dup2(pipe_data->pipe_fds[0], STDIN_FILENO);
	gc_close_fd(pipe_data->pipe_fds[0]);
	pipe_data->right_result = tree_monitor(node->right, NULL);
	destroy_minishell(pipe_data->right_result);
}

int	pipe_fork_error(t_pipe_data *pipe_data)
{
	kill(pipe_data->left_pid, SIGKILL);
	gc_close_fd(pipe_data->pipe_fds[0]);
	gc_close_fd(pipe_data->pipe_fds[1]);
	return (pec("Fork for right process failed"));
}

static void	close_pipe_and_wait(t_pipe_data *pipe_data)
{
	gc_close_fd(pipe_data->pipe_fds[0]);
	gc_close_fd(pipe_data->pipe_fds[1]);
	waitpid(pipe_data->left_pid, NULL, 0);
	waitpid(pipe_data->right_pid, &pipe_data->right_status, 0);
	main_signals();
}

int	pipe_monitor(t_ast_node *node)
{
	t_pipe_data	pipe_data;

	reset_signals();
	if (!node->left || !node->right)
	{
		get_shell()->exit_status = 2;
		return (pec("Invalid pipe node: missing children"));
	}
	if (pipe(pipe_data.pipe_fds) == -1)
		return (pec("Pipe creation failed"));
	pipe_data.left_pid = fork();
	if (pipe_data.left_pid == -1)
		return (pec("Fork for left process failed"));
	if (pipe_data.left_pid == 0)
		pipe_left_process(node, &pipe_data);
	pipe_data.right_pid = fork();
	if (pipe_data.right_pid == -1)
		return (pipe_fork_error(&pipe_data));
	if (pipe_data.right_pid == 0)
		pipe_right_process(node, &pipe_data);
	close_pipe_and_wait(&pipe_data);
	if (WIFEXITED(pipe_data.right_status))
		pipe_data.right_result = WEXITSTATUS(pipe_data.right_status);
	get_shell()->exit_status = pipe_data.right_result;
	return (pipe_data.right_result);
}
