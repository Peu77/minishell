/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:33:08 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:51:37 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_parentheses_fd(int fd_backup_stdout, int fd_backup_stdin)
{
	dup2(fd_backup_stdout, STDOUT_FILENO);
	dup2(fd_backup_stdin, STDIN_FILENO);
	close(fd_backup_stdout);
	close(fd_backup_stdin);
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
	int	fd_backup_stdout;
	int	fd_backup_stdin;

	fd_backup_stdout = dup(STDOUT_FILENO);
	fd_backup_stdin = dup(STDIN_FILENO);
	if (!node || node->type != AST_PARENTHESES)
		return (0);
	if (node->redirects)
		redirect_parentheses_monitor(node->redirects);
	if (node->left)
	{
		if (tree_monitor(node->left, command) != 0)
			return (1);
	}
	restore_parentheses_fd(fd_backup_stdout, fd_backup_stdin);
	return (0);
}
