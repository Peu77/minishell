/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:18 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 12:17:09 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int env(t_command_test *command)
{
    if (command->argument)
       return pec("env: too many arguments\n");
	print_env_list(command->env);
    return 0;
}
