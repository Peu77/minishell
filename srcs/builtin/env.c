/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:18 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:50:50 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_command *command)
{
	char **env;

	env = initialise_env(NULL);
	if (command->argument)
		return (print_error("env: No such file or directory \n"));
	print_env_list(env);
	return (0);
}
