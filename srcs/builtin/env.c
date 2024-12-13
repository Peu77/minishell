/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:18 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/13 21:11:19 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int env(t_command_test *command, t_env *env)
{
    if (command->argument)
       return pec("env: too many arguments\n");
	print_env_list(env);
    return 0;
}
