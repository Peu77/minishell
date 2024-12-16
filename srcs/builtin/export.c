/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:31 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 19:06:12 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strtok(char *str, const char delim)
{
	static char	*stock = NULL;
	static int	i = 0;
	char		*ptr;
	int			flg;

	flg = 0;
	ptr = NULL;
	if (str != NULL)
	{
		stock = ft_strdup(str);
		i = 0;
	}
	while (stock[i] != '\0')
	{
		if (flg == 0 && stock[i] != delim)
		{
			flg = 1;
			ptr = &stock[i];
		}
		else if (flg == 1 && stock[i] == delim)
		{
			stock[i] = '\0';
			i++;
			break ;
		}
		i++;
	}
	return (ptr);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	add_to_environ(const char *key_value_pair)
{
	char	**new_environ;
	size_t	env_count;
	size_t	i;

	env_count = 0;
	while (environ && environ[env_count])
		env_count++;
	new_environ = malloc(sizeof(char *) * (env_count + 2));
	if (!new_environ)
	{
		perror(ERROR_MALLOC);
		return (-1);
	}
	i = 0;
	while (i < env_count)
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[env_count] = ft_strdup(key_value_pair);
	if (!new_environ[env_count])
	{
		perror(ERROR_MALLOC);
		free(new_environ);
		return (-1);
	}
	new_environ[env_count + 1] = NULL;
	environ = new_environ;
	return (0);
}

int	ft_export(t_command_test *command)
{
	char	*arg;
	char	*pair;
	char	*equal_sign;

	arg = command->argument;
	if (!command || !command->argument)
		return (-1);
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
		if (add_to_environ(pair) < 0)
			return (1);
		pair = ft_strtok(NULL, ' ');
	}
	return (0);
}
