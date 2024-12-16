/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:49 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 07:00:33 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	and_monitor(t_ast_node *node, t_command_test *command)
{
	int	left_result;

	left_result = 0;
	if (node->left)
		left_result = tree_monitor(node->left, command);
	if (!left_result && node->right)
		return (tree_monitor(node->right, command));
	return (left_result);
}

int	or_monitor(t_ast_node *node, t_command_test *command)
{
	int	left_result;

	left_result = 0;
	if (node->left)
		left_result = tree_monitor(node->left, command);
	if (left_result && node->right)
		return (tree_monitor(node->right, command));
	return (left_result);
}
