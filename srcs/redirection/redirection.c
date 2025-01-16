/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/16 11:21:35 by ftapponn         ###   ########.fr       */
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
	int	from_fd;

	from_fd = STDOUT_FILENO;
	if (redirect->fd_left >= 0)
		from_fd = redirect->fd_left;
	if (redirect->file)
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = redirect->fd_right;
	if (fd == -1)
	{
		pev(ERROR_OPEN_FILE);
		return ;
	}
	if (dup2(fd, from_fd) == -1)
		pev("dup2 failed for output redirection");
	close(fd);
}

void	redirection_append(t_redirect *redirect)
{
	int	fd;
	int	from_fd;

	from_fd = STDOUT_FILENO;
	if (redirect->fd_left >= 0)
		from_fd = redirect->fd_left;
	fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		pev(ERROR_OPEN_FILE);
		return ;
	}
	if (dup2(fd, from_fd) == -1)
		pev("dup2 failed for output redirection");
	close(fd);
}

void	redirection_input(t_redirect *redirect)
{
	int	fd;
	int	from_fd;

	from_fd = STDIN_FILENO;
	if (redirect->fd_left >= 0)
		from_fd = redirect->fd_left;
	fd = open(redirect->file, O_RDONLY);
	if (fd == -1)
	{
		pev(ERROR_OPEN_FILE);
		return ;
	}
	if (dup2(fd, from_fd) == -1)
		pev("dup2 failed for input redirection");
	close(fd);
}
