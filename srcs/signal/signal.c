/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:10 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/19 19:07:51 by ftapponn         ###   ########.fr       */
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

void	main_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN); 
}

void sigint_command(int sig)
{
	(void)sig;
    destroy_minishell(130);
}

void signal_command(void)
{
    signal(SIGINT, sigint_command);
}

void	heredoc_sighandler(int sig)
{
	(void)sig;
	unlink("heredoc_temp.txt");
	destroy_minishell(130);
}
