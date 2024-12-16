/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:18 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 07:44:28 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_command_test *command)
{
	char **env = environ;
	if (command->argument)
		return (print_error("env: No such file or directory \n"));
	print_env_list(env);
	return (0);
}
