/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:37:15 by eebert            #+#    #+#             */
/*   Updated: 2025/01/16 23:09:53 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include <limits.h>

#include "../../includes/minishell.h"

int	ft_cd(t_command *command)
{
	char		**path;
	char		cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if(ft_strncmp(command->argument, "-", 2) == 0)
	{
		if (chdir(get_env_value("OLDPWD")) != 0)
			return (pec(ERROR_PATH));
		return (set_env_value("OLDPWD", cwd), 0);
	}
	path = ft_split(command->argument, ' ');
	if (!path)
		pec(ERROR_SPLIT);
	if (path[1])
		return (pec("cd : Too much argument"));
	if (chdir(path[0]) != 0)
	{
		free_string_array(path);
		return (pec(ERROR_PATH));
	}
	free_string_array(path);
	return (set_env_value("OLDPWD", cwd), 0);
}
