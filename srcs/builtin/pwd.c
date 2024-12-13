/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:42 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/13 22:13:33 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pwd(void) 
{
    char *buffer = malloc(MAX_PATH);
    if (buffer == NULL)
        return (0);
    if (getcwd(buffer, MAX_PATH) == NULL)
	{
		pe("error with getting path");
        free(buffer);
        return (1);
    }
	printf("%s \n", buffer);
	free(buffer);
	return (0);
}
