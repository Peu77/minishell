/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:44 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 20:13:34 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*construct_full_path(char *path, const char *command)
{
	char	*full_path;

	full_path = malloc(ft_strlen(path) + ft_strlen(command) + 2);
	if (!full_path)
		return (pev(ERROR_MALLOC), NULL);
	ft_strlcpy(full_path, path, ft_strlen(path) + 1);
	ft_strlcat(full_path, "/", ft_strlen(path) + ft_strlen(command) + 2);
	ft_strlcat(full_path, command, ft_strlen(path) + ft_strlen(command) + 2);
	return (full_path);
}

static char	*find_command_in_path(const char *command)
{
	char	*env_path;
	char	**paths;
	char	*full_path;
	int		i;

	i = -1;
	env_path = getenv("PATH");
	if (!env_path)
		return (pev(ERROR_FIND_ENV), NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (pev(ERROR_SPLIT), NULL);
	while (paths[++i])
	{
		full_path = construct_full_path(paths[i], command);
		if (!full_path)
			return (free_command_split(paths), NULL);
		if (access(full_path, F_OK) == 0)
			return (free_command_split(paths), full_path);
		free(full_path);
		full_path = NULL;
	}
	free_command_split(paths);
	return (NULL);
}

int	get_path(t_command_test **command)
{
	char	*found_path;

	found_path = find_command_in_path((*command)->command_name);
	if (found_path)
		(*command)->path = found_path;
	else
		(*command)->path = NULL;
	return (1);
}
