/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 00:31:42 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parse.h"

int	command_monitor(t_ast_node *node, t_command *command)
{
	char* tmp;
	int i;
	char** argv;

	 i = 0;
	if (!expand_string(node))
		return (-1);
	tmp = filter_and_get_redirects(node->value, &node->redirects);
	free(node->value);
	node->value = tmp;
	argv = split_quotes(node->value);
	free(node->value);
	if (!transform_node_to_command(argv, &command, node->redirects))
		return (0);
	while(command->argv[i])
	{
		command->argv[i] = ft_unescape_string(command->argv[i]);
		i++;
	}
	node->redirects = NULL;
	return (execution_monitor(command));
}
