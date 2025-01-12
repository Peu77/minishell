/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/12 11:30:31 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:06 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 18:50:13 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirection_output(t_redirect *redirect)
{
	int	fd;
	int	fromFd;

	fromFd = STDOUT_FILENO;
	if (redirect->fd_left >= 0)
		fromFd = redirect->fd_left;
	if (redirect->file)
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = redirect->fd_right;
	if (fd == -1)
	{
		pev("open failed for output redirection");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, fromFd) == -1)
	{
		pev("dup2 failed for output redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirection_append(t_redirect *redirect)
{
	int	fd;
	int	fromFd;

	fromFd = STDOUT_FILENO;
	if (redirect->fd_left >= 0)
		fromFd = redirect->fd_left;
	fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		pev("open failed for append redirection");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, fromFd) == -1)
	{
		pev("dup2 failed for append redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirection_input(t_redirect *redirect)
{
	int	fd;
	int	fromFd;

	fromFd = STDIN_FILENO;
	if (redirect->fd_left >= 0)
		fromFd = redirect->fd_left;
	fd = open(redirect->file, O_RDONLY);
	if (fd == -1)
	{
		pev("open failed for input redirection");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, fromFd) == -1)
	{
		pev("dup2 failed for input redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
