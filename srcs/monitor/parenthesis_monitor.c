/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:42:13 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 17:46:47 by eebert           ###   ########.fr       */
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
		redirects = redirects->next;
	}
}

int	parentheses_monitor(t_ast_node *node, t_command *command)
{
	t_parenthesis_fd	parenthesis_fd;
	int		redirect_exit_code;

	redirect_exit_code = EXIT_SUCCESS;
	expand_ast_node(node);
	if (parse_redirects_from_node(node, &redirect_exit_code))
		return (redirect_exit_code);

	parenthesis_fd.fd_backup_stdout = dup(STDOUT_FILENO);
	parenthesis_fd.fd_backup_stdin = dup(STDIN_FILENO);
	gc_add_fd(parenthesis_fd.fd_backup_stdout);
	gc_add_fd(parenthesis_fd.fd_backup_stdin);
	if (!node || node->type != AST_PARENTHESES)
		return (EXIT_SUCCESS);
	if (node->redirects)
		redirect_parentheses_monitor(node->redirects);
	if (node->heredoc_filename)
		redirect_input_from_heredoc(node->heredoc_filename);
	if (node->left && tree_monitor(node->left, command) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	restore_parentheses_fd(&parenthesis_fd);
	return (EXIT_SUCCESS);
}
