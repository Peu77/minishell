/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:01 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:50:45 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	ft_echo(t_command *command, bool is_n)
{
	char	*arg;

	arg = command->argument;
	while (arg && ft_strncmp(arg, "-n", 2) == 0 && (arg[2] == ' '
			|| arg[2] == '\0'))
	{
		arg += 2;
		while (*arg == ' ')
			arg++;
		is_n = true;
	}
	if (!arg || *arg == '\0')
	{
		if (!is_n)
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(arg, STDOUT_FILENO);
		if (is_n)
			ft_putstr_fd("\033[90m%\033[0m", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
