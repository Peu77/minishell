/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:33:08 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/21 17:24:54 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_parentheses_fd(t_parenthesis_fd *parenthesis_fd)
{
	dup2(parenthesis_fd->fd_backup_stdout, STDOUT_FILENO);
	dup2(parenthesis_fd->fd_backup_stdin, STDIN_FILENO);
	gc_close_fd(parenthesis_fd->fd_backup_stdout);
	gc_close_fd(parenthesis_fd->fd_backup_stdin);
}

void	redirect_parentheses_monitor(t_list *redirects)
{
	t_redirect	*redirect;

	while (redirects)
	{
		redirect = (t_redirect *)redirects->content;
		if (redirect->type == TOKEN_REDIRECT_OUTPUT)
			redirection_output(redirect);
		else if (redirect->type == TOKEN_REDIRECT_APPEND)
			redirection_append(redirect);
		else if (redirect->type == TOKEN_REDIRECT_INPUT)
			redirection_input(redirect);
		else if (redirect->type == TOKEN_REDIRECT_INPUT_APPEND)
			redirection_heredoc(redirect->file);
		redirects = redirects->next;
	}
}

int	parentheses_monitor(t_ast_node *node, t_command *command)
{
	t_parenthesis_fd	parenthesis_fd;

	parenthesis_fd.fd_backup_stdout = dup(STDOUT_FILENO);
	parenthesis_fd.fd_backup_stdin = dup(STDIN_FILENO);
	if (!node || node->type != AST_PARENTHESES)
		return (0);
	if (node->redirects)
		redirect_parentheses_monitor(node->redirects);
	if (node->left)
	{
		if (tree_monitor(node->left, command) != 0)
			return (1);
	}
	restore_parentheses_fd(&parenthesis_fd);
	return (0);
}
