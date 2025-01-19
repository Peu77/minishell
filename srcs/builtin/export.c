/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:36:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 14:41:24 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char* ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}



int	ft_export(t_command *command)
{
	char	*equal_sign;
	char	*plus_equal_sign;
	char	key[MAX_VAR_LEN];
	char	value[MAX_VAR_LEN];
	int		i;

	if (!command->argv[1])
		return (ft_env(command));
	i = 1;
	while (command->argv[i])
	{
		printf("argv[%d]: %s\n", i, command->argv[i]);
		equal_sign = ft_strchr(command->argv[i], '=');
		plus_equal_sign = ft_strnstr(command->argv[i], "+=", ft_strlen(command->argv[i]));
		printf("plus_equal_sign: %s\n", plus_equal_sign);
		if (plus_equal_sign && plus_equal_sign != command->argv[i])
		{
			ft_strncpy(key, command->argv[i], plus_equal_sign - command->argv[i]);
			key[plus_equal_sign - command->argv[i]] = '\0';
			ft_strncpy(value, plus_equal_sign + 2, MAX_VAR_LEN);
			char *existing_value = get_env_value(key);
			if (existing_value)
			{
				char *new_value = ft_strjoin(existing_value, value);
				if (!new_value)
					return (1);
				if (!set_env_value(key, new_value))
					return (1);
				free(new_value);
			}
			else
			{
				if (!set_env_value(key, value))
					return (1);
			}
		}
		else if (equal_sign)
		{
			ft_strncpy(key, command->argv[i], equal_sign - command->argv[i]);
			key[equal_sign - command->argv[i]] = '\0';
			ft_strncpy(value, equal_sign + 1, MAX_VAR_LEN);
			if (!set_env_value(key, value))
				return (1);
		}
		else
		{
			if (!is_valid_identifier(command->argv[i]))
				return (print_error(ERROR_EXPORT));
			if (!set_env_value(command->argv[i], ""))
				return (1);
		}
		i++;
	}
	return (0);
}