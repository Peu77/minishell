/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:49 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 18:44:41 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_command_test *command, t_env *env)
{
	char	**arg;
	int		result;
	int		unset_result;

	arg = ft_split(command->argument, ' ');
	result = 0;
	while (*arg)
	{
		unset_result = unset_variable(env, *arg);
		if (unset_result != 0)
			result = 1;
		arg++;
	}
	print_env_list(env);
	return (result);
}
