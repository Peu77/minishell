/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2024/12/16 20:13:16 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parse.h"

int	command_monitor(t_ast_node *node, t_command_test *command)
{
	t_list	*redirect;

	redirect = NULL;
	if (node->redirects)
		redirect = node->redirects;
	parse_env_variables(node);
	transform_node_to_command(node->value, &command, redirect);
	return (execution_monitor(command));
}
