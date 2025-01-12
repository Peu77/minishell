/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/12 19:51:32 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parse.h"

int	command_monitor(t_ast_node *node, t_command *command)
{
	interpret_command_string(node);
	transform_node_to_command(node->value, &command, node->redirects);
	node->redirects = NULL;
	return (execution_monitor(command));
}
