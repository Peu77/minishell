/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 20:36:24 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parse.h"

int	command_monitor(t_ast_node *node, t_command *command)
{
	char* tmp;
	int i;
	char** argv;
	int redirect_exit_code;

	 i = 0;
	redirect_exit_code = 0;
	tmp = expand_string(node->value);
	gc_free_ptr(node->value);
	node->value = tmp;
	tmp = expand_wildcards(node->value);
	gc_free_ptr(node->value);
	node->value = tmp;
	tmp = filter_and_get_redirects(node->value, &node->redirects, &redirect_exit_code);
	gc_free_ptr(node->value);
	if(redirect_exit_code != 0) {
		get_shell()->exit_status = redirect_exit_code;
		if(redirect_exit_code == 258)
			pe("parse error, each redirect should have an filename");
		return (redirect_exit_code);
	}
	node->value = tmp;
	argv = split_quotes(node->value);
	gc_free_ptr(node->value);
	while(argv[i])
	{
		argv[i] = ft_unescape_string(argv[i]);
		i++;
	}
	if (!transform_node_to_command(argv, &command, node->redirects))
		return (1);

	node->redirects = NULL;
	return (execution_monitor(command));
}
