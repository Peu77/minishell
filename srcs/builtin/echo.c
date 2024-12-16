/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:01 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 18:58:34 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_command_test *command, bool is_n)
{
	if (!command->argument && !is_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (!is_n)
	{
		ft_putstr_fd(command->argument, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		ft_putstr_fd(command->argument, STDOUT_FILENO);
	return (0);
}
