/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:03:16 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/23 19:03:25 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_command(int sig)
{
	(void)sig;
	destroy_minishell(130);
}

static void	sigquit_command(int sig)
{
	(void)sig;
	destroy_minishell(131);
}

void	command_signals(void)
{
	signal(SIGINT, sigint_command);
	signal(SIGQUIT, sigquit_command);
}
