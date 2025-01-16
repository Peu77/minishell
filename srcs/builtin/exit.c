/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:53:37 by eebert            #+#    #+#             */
/*   Updated: 2025/01/16 21:25:16 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free_string_array(*cmd);
		return (pec(ERROR_TOO_ARGUMENT));
	}
	i = -1;
	while ((*cmd)[0][++i] != '\0')
	{
		if (!ft_isdigit((*cmd)[0][i]))
		{
			free_string_array(*cmd);
			return (pec(ERROR_DIGIT_ARGUMENT));
		}
	}
	return (0);
}

int	ft_exit(t_command *command)
{
	char	**cmd;

	if (command->argument == NULL)
	{
		get_shell()->shell_exit_code = EXIT_SUCCESS;
		get_shell()->should_exit = true;
		return (0);
	}
	if (validate_exit_arguments(command->argument, &cmd) != 0)
		return (-1);
	get_shell()->shell_exit_code = ft_atol(cmd[0]) % 255;
	free_string_array(cmd);
	get_shell()->should_exit = true;
	return (0);
}
