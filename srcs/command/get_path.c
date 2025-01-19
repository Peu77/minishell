/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:37:15 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 17:35:33 by eebert           ###   ########.fr       */
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
	env_path = get_env_value("PATH");
	if (!env_path)
		return (pev(ERROR_FIND_ENV), NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (pev(ERROR_SPLIT), NULL);
	while (paths[++i])
	{
		full_path = construct_full_path(paths[i], command);
		if (!full_path)
			return (free_string_array(paths), NULL);
		if (access(full_path, F_OK) == 0)
			return (free_string_array(paths), full_path);
		free(full_path);
		full_path = NULL;
	}
	free_string_array(paths);
	return (NULL);
}

int	get_path(t_command **command)
{
	char	*found_path;

	(*command)->path = ft_strdup((*command)->command_name);
	found_path = find_command_in_path((*command)->command_name);
	if (found_path)
	{
		free((*command)->path);
		(*command)->path = found_path;
	}
	return (1);
}
