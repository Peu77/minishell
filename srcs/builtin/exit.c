/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:53:37 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 13:28:47 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_exit_arguments(char **argv)
{
	size_t	i;

	i = 0;
	if (argv[1][0] == 0)
		return (pe(ERROR_DIGIT_ARGUMENT), 255);
	while ((argv)[1][i] != '\0' && ft_isspace(argv[1][i]))
		i++;
	if (argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	while ((argv)[1][i] != '\0')
	{
		if (!ft_isdigit((argv)[1][i]))
			return (pe(ERROR_DIGIT_ARGUMENT), 255);
		i++;
	}
	if ((argv)[2])
		return (pec(ERROR_TOO_ARGUMENT));
	return (0);
}

int	ft_exit(t_command *command)
{
	int	validate_exit_status;

	get_shell()->should_exit = true;
	if (command->argv[1] == NULL)
	{
		get_shell()->exit_status = EXIT_SUCCESS;
		get_shell()->should_exit = true;
		return (0);
	}
	validate_exit_status = validate_exit_arguments(command->argv);
	if (validate_exit_status != 0)
		return (validate_exit_status);
	return (ft_atoi(command->argv[1]) % 256);
}
