/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:49 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/18 20:15:07 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_variable_from_env(char *var_to_remove)
{
	char	**envp;
	char	**current;

	envp = initialise_env(NULL, 2);
	while (*envp)
	{
		if (strncmp(*envp, var_to_remove, strlen(var_to_remove)) == 0
			&& (*envp)[strlen(var_to_remove)] == '=')
		{
			current = envp;
			while (*current)
			{
				*current = *(current + 1);
				current++;
			}
			return (0);
		}
		envp++;
	}
	return (-1);
}

int	ft_unset(t_command_test *command)
{
	char	**arg;
	int		result;

	arg = ft_split(command->argument, ' ');
	result = 0;
	while (*arg)
	{
		if (remove_variable_from_env(*arg) != 0)
			result = -1;
		arg++;
	}
	return (result);
}
