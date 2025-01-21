/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 13:37:19 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parse.h"

static void	process_expansions(t_ast_node *node)
{
	char	*tmp;

	tmp = expand_string(node->value);
	gc_free_ptr(node->value);
	node->value = tmp;
	tmp = expand_wildcards(node->value);
	gc_free_ptr(node->value);
	node->value = tmp;
}

static int	handle_redirects(t_ast_node *node, int *redirect_exit_code)
{
	char	*tmp;

	tmp = filter_and_get_redirects(node->value, &node->redirects,
			redirect_exit_code);
	gc_free_ptr(node->value);
	node->value = tmp;
	if (*redirect_exit_code != 0)
	{
		get_shell()->exit_status = *redirect_exit_code;
		if (*redirect_exit_code == 258)
			pe("parse error, each redirect should have an filename");
		return (1);
	}
	return (0);
}

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
	if (!transform_node_to_command(argv, &cmd, node->redirects))
		return (1);
	node->redirects = NULL;
	return (execution_monitor(cmd));
}

int	command_monitor(t_ast_node *node, t_command *command)
{
	char	**argv;
	int		redirect_exit_code;

	redirect_exit_code = 0;
	process_expansions(node);
	if (handle_redirects(node, &redirect_exit_code))
		return (redirect_exit_code);
	argv = process_arguments(node);
	return (execute_transformed_command(node, command, argv));
}
