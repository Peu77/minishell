/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:42 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/12 19:51:01 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_command *command)
{
	char	*buffer;

	if (command->argument)
		return (print_error(ERROR_PWD));
	buffer = malloc(MAX_PATH);
	if (buffer == NULL)
		return (0);
	if (getcwd(buffer, MAX_PATH) == NULL)
	{
		free(buffer);
		return (pec("error with getting path"));
	}
	printf("%s \n", buffer);
	free(buffer);
	return (0);
}
