/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:35:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 00:01:14 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool is_n_flag(char *str)
{
	int i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int ft_echo(t_command *command, bool is_n)
{
	int i;
	bool first_word;

	if (!command->argv || !command->argv[1])
	{
		if (!is_n)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	i = 1;
	while (command->argv[i] && is_n_flag(command->argv[i]))
	{
		is_n = true;
		i++;
	}
	first_word = true;
	while (command->argv[i])
	{
		if (!first_word)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(command->argv[i], STDOUT_FILENO);
		first_word = false;
		i++;
	}
	if (!is_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}