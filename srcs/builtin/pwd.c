/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:42 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/21 18:04:48 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_command *command)
{
	char	*buffer;

	if (command->argv[1])
		return (print_error(ERROR_PWD));
	buffer = gc_malloc(MAX_PATH);
	if (buffer == NULL)
		return (0);
	if (getcwd(buffer, MAX_PATH) == NULL)
	{
		gc_free_ptr(buffer);
		return (pec("error with getting path"));
	}
	printf("%s \n", buffer);
	gc_free_ptr(buffer);
	return (0);
}
