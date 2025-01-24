/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:23 by eebert            #+#    #+#             */
/*   Updated: 2025/01/24 15:50:08 by eebert           ###   ########.fr       */
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

bool traverse_heredocs(t_ast_node *node) {
	t_list * redirects;
	t_list* tmp;
	int exit_code;

	redirects = NULL;
	if (!node)
		return (true);
	if (node->type != AST_COMMAND) {
		if (!traverse_heredocs(node->left))
			return (false);
		if (!traverse_heredocs(node->right))
			return (false);
		return true;
	}

	gc_free_ptr(filter_and_get_redirects(node->value, &redirects, &exit_code));
	tmp = redirects;
	while (tmp) {
		if (((t_redirect*) tmp->content)->type == TOKEN_REDIRECT_INPUT_APPEND) {
			 redirection_heredoc(((t_redirect*) tmp->content)->file, node);
		}
		tmp = tmp->next;
	}

	gc_list_clear(&redirects, free_redirect);
	return true;
}
