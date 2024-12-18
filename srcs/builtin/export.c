/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:31 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/18 19:39:57 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	variable_exists(const char *key_value_pair)
{
	char	*equal_sign;
	char 	**environ;
	size_t	name_len;
	size_t	i;

	environ = initialise_env(NULL, 1);
	equal_sign = ft_strchr(key_value_pair, '=');
	if (!equal_sign)
		return (0);
	name_len = equal_sign - key_value_pair;
	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], key_value_pair, name_len) == 0
			&& environ[i][name_len] == '=')
			return (1);
		i++;
	}
	initialise_env(environ, 2);
	return (0);
}

int	add_to_environ(const char *key_value_pair)
{
	char	**new_environ;
	size_t	env_count;
	size_t	i;

	environ = initialise_env(NULL, 2);
	if (variable_exists(key_value_pair))
		return (0);
	env_count = 0;
	while (environ && environ[env_count])
		env_count++;
	new_environ = malloc(sizeof(char *) * (env_count + 2));
	if (!new_environ)
		return (pec(ERROR_MALLOC));
	i = -1;
	while (++i < env_count)
		new_environ[i] = environ[i];
	new_environ[env_count] = ft_strdup(key_value_pair);
	if (!new_environ[env_count])
	{
		free(new_environ);
		return (pec(ERROR_MALLOC));
	}
	new_environ[env_count + 1] = NULL;
	initialise_env(environ, 2);
	return (0);
}

int	ft_export(t_command_test *command)
{
	char	*arg;
	char	*pair;
	char	*equal_sign;

	arg = command->argument;
	if (!command || !command->argument)
		return (1);
	pair = ft_strtok(arg, ' ');
	while (pair)
	{
		equal_sign = ft_strchr(pair, '=');
		if (!equal_sign || equal_sign == pair || !is_valid_identifier(pair))
		{
			if (!is_valid_identifier(pair))
				return (print_error(ERROR_EXPORT));
			return (0);
		}
		if (add_to_environ(pair) == 1)
			return (1);
		pair = ft_strtok(NULL, ' ');
	}
	return (0);
}
