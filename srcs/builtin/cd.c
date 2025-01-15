/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:52 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:50:42 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_command *command)
{
	char	**path;
	const char *home ;

	home = get_env_value("HOME", get_shell()->env);

	if (!command->argument || ft_strncmp(command->argument, "~", 2) == 0)
	{
		if (!home || chdir(home) != 0)
			return (pec(ERROR_PATH));
		return (1);
	}
	path = ft_split(command->argument, ' ');
	if (!path)
		pec(ERROR_SPLIT);
	if(path[1])
		return (pec("cd : Too much argument"));
	if (chdir(path[0]) != 0)
	{
		free_command_split(path);
		return (pec(ERROR_PATH));
	}
	free_command_split(path);
	return (0);
}
