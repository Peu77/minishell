/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:33:08 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 20:33:09 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parentheses_monitor(t_ast_node *node, t_command_test *command)
{
	if (!node || node->type != AST_PARENTHESES)
		return (0);
	if (node->left)
	{
		if (tree_monitor(node->left, command) != 0)
			return (1);
	}
	return (0);
}
