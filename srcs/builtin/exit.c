/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:24 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:50:54 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_exit_arguments(char *argument, char ***cmd)
{
	int	i;

	*cmd = ft_split(argument, ' ');
	if (!*cmd)
		return (pec(ERROR_SPLIT));
	if ((*cmd)[1])
	{
		free_command_split(*cmd);
		return (pec(ERROR_TOO_ARGUMENT));
	}
	i = -1;
	while ((*cmd)[0][++i] != '\0')
	{
		if (!ft_isdigit((*cmd)[0][i]))
		{
			free_command_split(*cmd);
			return (pec(ERROR_DIGIT_ARGUMENT));
		}
	}
	return (0);
}

int	ft_exit(t_command *command)
{
	char	**cmd;
	long	exit_code;

	if (command->argument == NULL)
		exit(EXIT_SUCCESS);
	if (validate_exit_arguments(command->argument, &cmd) != 0)
		return (-1);
	exit_code = ft_atol(cmd[0]) % 255;
	free_command_split(cmd);
	exit((int)exit_code);
}
