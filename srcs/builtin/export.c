/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:36:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/18 23:38:23 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_export(t_command *command)
{
	char	*equal_sign;
	char	key[MAX_VAR_LEN];
	char	value[MAX_VAR_LEN];
	int		i;

	if (!command->argv[1])
		return (ft_env(command));
	i = 1;
	while (command->argv[i])
	{
		equal_sign = ft_strchr(command->argv[i], '=');
		if (!equal_sign || equal_sign == command->argv[i]
			|| !is_valid_identifier(command->argv[i]))
			return (print_error(ERROR_EXPORT));
		split_env_pairstr(command->argv[i], key, value);
		if (!set_env_value(key, value))
			return (1);
		i++;
	}
	return (0);
}
