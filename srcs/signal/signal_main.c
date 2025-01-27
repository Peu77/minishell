/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:10:37 by eebert            #+#    #+#             */
/*   Updated: 2025/01/27 18:06:34 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:10 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/23 19:02:35 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sighandler(int sig)
{
	char	*prompt;

	(void)sig;
	prompt = create_prompt();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\n%s", prompt);
	gc_free_ptr(prompt);
}

static void	sigtstp_command(int sig)
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
