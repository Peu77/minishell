/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:03:09 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/23 19:04:08 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_sighandler(int sig)
{
	(void)sig;
	unlink("heredoc_temp.txt");
	destroy_minishell(130);
}

void	signal_heredoc(void)
{
	signal(SIGINT, heredoc_sighandler);
	signal(SIGTSTP, SIG_IGN);
}
