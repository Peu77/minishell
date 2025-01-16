/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:36:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/16 20:40:54 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:31 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/13 19:00:52 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_export(t_command *command)
{
	char	*arg;
	char	*pair;
	char	*equal_sign;

	arg = command->argument;
	if (!command || !command->argument)
		return (ft_env(command));
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
		if (add_env_pairstr(pair) == 1)
			return (1);
		pair = ft_strtok(NULL, ' ');
	}
	return (0);
}
