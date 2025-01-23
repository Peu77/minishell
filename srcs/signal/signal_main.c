/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:10 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/23 16:33:26 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sighandler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\n>>>> Minishell>$ ");
}

static void sigtstp_command(int sig)
{
	(void)sig;
	destroy_minishell(131);
}

void	main_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, sigtstp_command); 
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
