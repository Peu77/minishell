/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 17:37:47 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parse.h"

static char	**process_arguments(t_ast_node *node)
{
	char	**argv;
	int		i;

	argv = split_quotes(node->value);
	gc_free_ptr(node->value);
	node->value = NULL;
	i = 0;
	while (argv[i])
	{
		argv[i] = ft_unescape_string(argv[i]);
		i++;
	}
	return (argv);
}

static int	execute_transformed_command(t_ast_node *node, t_command *cmd,
		char **argv)
{
	if (!transform_node_to_command(argv, &cmd, node->redirects,
			node->heredoc_filename))
		return (1);
	node->redirects = NULL;
	return (execution_monitor(cmd));
}

int	command_monitor(t_ast_node *node, t_command *command)
{
	char	**argv;
	int		redirect_exit_code;

	redirect_exit_code = 0;
	expand_ast_node(node);
	if (parse_redirects_from_node(node, &redirect_exit_code))
		return (redirect_exit_code);
	argv = process_arguments(node);
	return (execute_transformed_command(node, command, argv));
}
