/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:23 by eebert            #+#    #+#             */
/*   Updated: 2025/01/24 16:58:35 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tree_monitor(t_ast_node *node, t_command *command)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (pipe_monitor(node));
	if (node->type == AST_AND)
		return (and_monitor(node, command));
	if (node->type == AST_OR)
		return (or_monitor(node, command));
	if (node->type == AST_SEMICOLON)
		return (semicolon_monitor(node, command));
	if (node->type == AST_PARENTHESES)
		return (parentheses_monitor(node, command));
	if (node->type == AST_COMMAND)
		return (command_monitor(node, command));
	return (0);
}

static bool	handle_non_command_nodes(t_ast_node *node)
{
	if (!traverse_heredocs(node->left))
		return (false);
	if (!traverse_heredocs(node->right))
		return (false);
	return (true);
}

static bool	process_heredoc(t_list *redirects, t_ast_node *node)
{
	t_list		*current;
	t_redirect	*redirect;

	current = redirects;
	while (current)
	{
		redirect = (t_redirect *)current->content;
		if (redirect->type == TOKEN_REDIRECT_INPUT_APPEND)
		{
			if (!redirection_heredoc(redirect->file, node))
				return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	traverse_heredocs(t_ast_node *node)
{
	t_list	*redirects;
	int		exit_code;

	if (!node)
		return (true);
	if (node->type != AST_COMMAND)
		return (handle_non_command_nodes(node));
	redirects = NULL;
	gc_free_ptr(filter_and_get_redirects(node->value, &redirects, &exit_code));
	if (!process_heredoc(redirects, node))
	{
		gc_list_clear(&redirects, free_redirect);
		return (false);
	}
	gc_list_clear(&redirects, free_redirect);
	return (true);
}
