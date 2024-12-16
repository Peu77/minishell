/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:23 by eebert            #+#    #+#             */
/*   Updated: 2024/12/16 06:58:45 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tree_monitor(t_ast_node *node, t_command_test *command)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (pipe_monitor(node));
	if (node->type == AST_AND)
		return (and_monitor(node, command));
	if (node->type == AST_OR)
		return (or_monitor(node, command));
	if (node->type == AST_COMMAND)
		return (command_monitor(node, command));
	return (0);
}
