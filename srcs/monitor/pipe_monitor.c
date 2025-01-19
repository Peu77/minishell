/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:04 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/19 16:24:58 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_left_process(t_ast_node *node, t_pipe_data *pipe_data)
{
	close(pipe_data->pipe_fds[0]);
	dup2(pipe_data->pipe_fds[1], STDOUT_FILENO);
	close(pipe_data->pipe_fds[1]);
	exit(tree_monitor(node->left, NULL));
}

int	pipe_right_process(t_ast_node *node, t_pipe_data *pipe_data)
{
	close(pipe_data->pipe_fds[1]);
	dup2(pipe_data->pipe_fds[0], STDIN_FILENO);
	close(pipe_data->pipe_fds[0]);
	pipe_data->right_result = tree_monitor(node->right, NULL);
	exit(pipe_data->right_result);
}

int	pipe_fork_error(t_pipe_data *pipe_data)
{
	kill(pipe_data->left_pid, SIGKILL);
	close(pipe_data->pipe_fds[0]);
	close(pipe_data->pipe_fds[1]);
	return (pec("Fork for right process failed"));
}

int	pipe_monitor(t_ast_node *node)
{
	t_pipe_data	pipe_data;

    reset_signals();
	if (!node->left || !node->right)
		return (pec("Invalid pipe node: missing children"));
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
	close(pipe_data.pipe_fds[0]);
	close(pipe_data.pipe_fds[1]);
	waitpid(pipe_data.left_pid, NULL, 0);
	waitpid(pipe_data.right_pid, &pipe_data.right_status, 0);
	main_signals();
	if (WIFEXITED(pipe_data.right_status))
		pipe_data.right_result = WEXITSTATUS(pipe_data.right_status);
	return (pipe_data.right_result);
}
