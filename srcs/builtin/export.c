/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:36:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 13:54:40 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_export(t_command *command)
{
	char	**args;
	char	*equal_sign;
	char	key[MAX_VAR_LEN];
	char	value[MAX_VAR_LEN];
	int		i;

	if (!command->argument)
		return (ft_env(command));
	args = ft_split(command->argument, ' ');
	i = 0;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (!equal_sign || equal_sign == args[i]
			|| !is_valid_identifier(args[i]))
			return (print_error(ERROR_EXPORT));
		split_env_pairstr(args[i], key, value);
		if (!set_env_value(key, value))
			return (free_string_array(args), 1);
		i++;
	}
	free_string_array(args);
	return (0);
}
