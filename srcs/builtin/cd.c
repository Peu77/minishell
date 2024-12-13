/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:52 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/13 21:10:54 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int cd(t_command_test *command)
{
	char **path;
	if (!command->argument)
	{
		if (chdir("/") != 0) 
			return pec(ERROR_PATH);
		return(1);
	}
	path = ft_split(command->argument, ' ');
	if(!path)
		pec(ERROR_SPLIT);
	if (chdir(path[0]) != 0) 
	{
		free_command_split(path);
		return pec(ERROR_PATH);
	}
	free_command_split(path);
	return (0);
}
