/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:49 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/13 21:11:50 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int unset(t_command_test *command, t_env *env)
{
    char **arg = ft_split(command->argument, ' ');
    int result = 0;
	int unset_result;

    while (*arg)
    {
        unset_result = unset_variable(env, *arg);
        if (unset_result != 0)
            result = 1;
        arg++;
    }
    return result;
}


