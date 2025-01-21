/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:30:09 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 13:21:47 by ftapponn         ###   ########.fr       */
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

bool	redirection_output(t_redirect *redirect)
{
	int	fd;
	int	from_fd;

	from_fd = STDOUT_FILENO;
	if (redirect->fd_left >= 0)
		from_fd = redirect->fd_left;
	if (redirect->file)
		fd = gc_add_fd(open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC,
					0644));
	else
		fd = redirect->fd_right;
	if (fd == -1)
	{
		pev(ERROR_OPEN_FILE);
		return (false);
	}
	if (dup2(fd, from_fd) == -1)
		return (gc_close_fd(fd), pe("dup2 failed for output redirection"),
			false);
	gc_close_fd(fd);
	return (true);
}

bool	redirection_append(t_redirect *redirect)
{
	int	fd;
	int	from_fd;

	from_fd = STDOUT_FILENO;
	if (redirect->fd_left >= 0)
		from_fd = redirect->fd_left;
	if (redirect->file)
		fd = gc_add_fd(open(redirect->file, O_WRONLY | O_CREAT | O_APPEND,
					0644));
	else
		fd = redirect->fd_right;
	if (fd == -1)
	{
		pev(ERROR_OPEN_FILE);
		return (false);
	}
	if (dup2(fd, from_fd) == -1)
		return (gc_close_fd(fd), pe("dup2 failed for output redirection"),
			false);
	gc_close_fd(fd);
	return (true);
}

bool	redirection_input(t_redirect *redirect)
{
	int	fd;
	int	from_fd;

	from_fd = STDIN_FILENO;
	if (redirect->fd_left >= 0)
		from_fd = redirect->fd_left;
	if (redirect->file)
		fd = gc_add_fd(open(redirect->file, O_RDONLY));
	else
		fd = redirect->fd_right;
	if (fd == -1)
	{
		pev(ERROR_OPEN_FILE);
		return (false);
	}
	if (dup2(fd, from_fd) == -1)
		return (gc_close_fd(fd), pe("dup2 failed for input redirection"),
			false);
	gc_close_fd(fd);
	return (true);
}
