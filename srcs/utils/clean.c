/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:46 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 19:18:28 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	free_command_split(char **command_split)
{
	int	i;

	i = -1;
	if (!command_split)
		return ;
	while (command_split[++i])
		free(command_split[i]);
	free(command_split);
}

void	free_command(t_command_test **command)
{
	if (!command || !*command)
		return ;
	if ((*command)->path)
	{
		free((*command)->path);
		(*command)->path = NULL;
	}
	if ((*command)->command_name)
	{
		free((*command)->command_name);
		(*command)->command_name = NULL;
	}
	if ((*command)->argument)
	{
		free((*command)->argument);
		(*command)->argument = NULL;
	}
	if ((*command)->redirect)
	{
		ft_lstclear(&(*command)->redirect, free);
		(*command)->redirect = NULL;
	}
	free(*command);
	*command = NULL;
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->variable_name);
		free(tmp->variable_value);
		free(tmp);
	}
}
