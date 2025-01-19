/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:37:15 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 00:00:08 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

int	ft_cd(t_command *command)
{
	char	cwd[PATH_MAX];
	char* oldpwd;

	getcwd(cwd, sizeof(cwd));
	if(command->argv[2] != NULL)
		return (pec("cd : Too much argument"));
	if (ft_strncmp(command->argv[1], "-", 2) == 0 || ft_strncmp(command->argv[1], "--", 3) == 0)
	{
		oldpwd = get_env_value("OLDPWD");
		if(!oldpwd || !*oldpwd)
			return (pec("OLDPWD not set"));
		if (chdir(oldpwd) != 0)
			return (pec(ERROR_PATH));
		printf("%s\n", oldpwd);
		return (set_env_value("PWD", get_env_value("OLDPWD")), set_env_value("OLDPWD", cwd), 0);
	}
	if (chdir(command->argv[1]) != 0)
		return (pec(ERROR_PATH));
	set_env_value("OLDPWD", cwd);
	getcwd(cwd, sizeof(cwd));
	return (set_env_value("PWD", cwd), 0);
}
