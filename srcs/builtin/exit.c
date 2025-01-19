/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:53:37 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 22:59:58 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_exit_arguments(char** argv)
{
	int	i;

	if ((argv)[2])
		return (pec(ERROR_TOO_ARGUMENT));
	i = -1;
	while ((argv)[1][++i] != '\0')
	{
		if (!ft_isdigit((argv)[1][i]))
			return (pec(ERROR_DIGIT_ARGUMENT));
	}
	return (0);
}

int	ft_exit(t_command *command)
{
	if (command->argv[1] == NULL)
	{
		get_shell()->exit_status = EXIT_SUCCESS;
		get_shell()->should_exit = true;
		return (0);
	}
	if (validate_exit_arguments(command->argv) != 0)
		return (-1);
	get_shell()->should_exit = true;
	return (ft_atoi(command->argv[1]) % 256);
}
