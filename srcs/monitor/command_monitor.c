/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:58 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 12:18:16 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int command_monitor(t_ast_node *node, t_command_test *command, t_env *env)
{
    t_list* redirect = NULL;

    if (node->redirects)
        redirect = node->redirects;
    transform_node_to_command(node->value, &command, redirect, env);
    return execution_monitor(command);
}
