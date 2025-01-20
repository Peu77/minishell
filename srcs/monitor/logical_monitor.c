/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:35:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 16:14:27 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:49 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:51:27 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	and_monitor(t_ast_node *node, t_command *command)
{
	int	left_result;

	left_result = 0;
	if (node->left)
		left_result = tree_monitor(node->left, command);
	if (!left_result && node->right)
		return (tree_monitor(node->right, command));
	return (left_result);
}

int	or_monitor(t_ast_node *node, t_command *command)
{
	int	left_result;

	left_result = 0;
	if (node->left)
		left_result = tree_monitor(node->left, command);
	if (left_result && node->right)
		return (tree_monitor(node->right, command));
	return (left_result);
}

int	semicolon_monitor(t_ast_node *node, t_command *command)
{
	int	left_result;

	left_result = 0;
	if (node->left)
		left_result = tree_monitor(node->left, command);
	if (node->right)
		return (tree_monitor(node->right, command));
	return (left_result);
}
