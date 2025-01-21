/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:23:59 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 13:35:06 by ftapponn         ###   ########.fr       */
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

/*
void	print_node_left(t_ast_node *node) {
	if (node) {
		// First, check and print information about the left node
		if (node->left) {
			printf("Left node - value: %s, type: %d\n", node->left->value,
				node->left->type);

			// Now, check and print the redirects for the left node
			if (node->left->redirects) {
				t_list *current_redirect = node->left->redirects;

				// Iterate over the list of redirects
				while (current_redirect) {
					// Cast the content of the current list node to t_redirect
					t_redirect *redirect = (t_redirect *)current_redirect->content;

					// Print the details of the current redirect
					printf("Redirect (left node) - fd_left: %d, fd_right: %d,
						file: %s, type: %d\n",
							redirect->fd_left, redirect->fd_right,
								redirect->file, redirect->type);

					// Move to the next redirect in the list
					current_redirect = current_redirect->next;
				}
			} else {
				printf("No redirects in the left node.\n");
			}

		} else {
			printf("No left node.\n");
		}
	}
}
*/

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
	// print_node_left(node);
	if (pipe_data.left_pid == 0)
	{
		pipe_left_process(node, &pipe_data);
	}
	pipe_data.right_pid = fork();
	if (pipe_data.right_pid == -1)
		return (pipe_fork_error(&pipe_data));
	if (pipe_data.right_pid == 0)
		pipe_right_process(node, &pipe_data);
	gc_close_fd(pipe_data.pipe_fds[0]);
	gc_close_fd(pipe_data.pipe_fds[1]);
	waitpid(pipe_data.left_pid, NULL, 0);
	waitpid(pipe_data.right_pid, &pipe_data.right_status, 0);
	main_signals();
	if (WIFEXITED(pipe_data.right_status))
		pipe_data.right_result = WEXITSTATUS(pipe_data.right_status);
	get_shell()->exit_status = pipe_data.right_result;
	return (pipe_data.right_result);
}
