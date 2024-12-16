/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:46 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 06:57:21 by ftapponn         ###   ########.fr       */
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

