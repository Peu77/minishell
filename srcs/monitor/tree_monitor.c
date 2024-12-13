/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:23 by eebert            #+#    #+#             */
/*   Updated: 2024/12/13 11:24:04 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int tree_monitor(t_ast_node *node, t_command_test *command, t_env *env)
{
    if (!node)
        return 0;

    if (node->type == AST_PIPE)
        return pipe_monitor(node, env);
    if (node->type == AST_AND)
        return and_monitor(node, command, env);
    if (node->type == AST_OR)
        return or_monitor(node, command, env);
    if (node->type == AST_COMMAND)
        return command_monitor(node, command, env);

    return 0;
}
