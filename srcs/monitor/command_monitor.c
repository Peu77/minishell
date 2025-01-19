/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 13:23:16 by eebert           ###   ########.fr       */
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
	tmp = expand_string(node->value);
	if(!tmp)
		return (1);
	free(node->value);
	node->value = tmp;
	tmp = expand_wildcards(node->value);
	if(!tmp)
		return (1);
	free(node->value);
	node->value = tmp;
	tmp = filter_and_get_redirects(node->value, &node->redirects);
	if (!tmp)
		return (1);
	free(node->value);
	node->value = tmp;
	argv = split_quotes(node->value);
	free(node->value);
	if (!transform_node_to_command(argv, &command, node->redirects))
		return (1);
	while(command->argv[i])
	{
		command->argv[i] = ft_unescape_string(command->argv[i]);
		i++;
	}
	node->redirects = NULL;
	return (execution_monitor(command));
}
