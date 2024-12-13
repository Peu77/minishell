/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:09:53 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/13 21:09:56 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pe(const char *message)
{
    write(STDERR_FILENO, RED, ft_strlen(RED));
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, RESET, ft_strlen(RESET));
    write(STDERR_FILENO, "\n", 1);
	return (0);
}

void pev(const char *message)
{
    write(STDERR_FILENO, RED, ft_strlen(RED));
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, RESET, ft_strlen(RESET));
    write(STDERR_FILENO, "\n", 1);
}

int pec(const char *message)
{
    write(STDERR_FILENO, RED, ft_strlen(RED));
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, RESET, ft_strlen(RESET));
    write(STDERR_FILENO, "\n", 1);
	return (1);
}
