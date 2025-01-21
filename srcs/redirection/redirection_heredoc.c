/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:44:20 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 13:49:06 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:25 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/19 19:31:52 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_heredoc_input(int temp_fd, const char *delimiter)
{
	char	*buffer;

	while (1)
	{
		buffer = gc_add(readline("heredoc> "));
		if (buffer == NULL)
		{
			write(temp_fd, "\n", 1);
			break ;
		}
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			gc_free_ptr(buffer);
			break ;
		}
		write(temp_fd, buffer, ft_strlen(buffer));
		write(temp_fd, "\n", 1);
		gc_free_ptr(buffer);
	}
}

static void	create_heredoc_file(const char *delimiter)
{
	int	temp_fd;

	signal(SIGINT, heredoc_sighandler);
	temp_fd = gc_add_fd(open("heredoc_temp.txt", O_WRONLY | O_CREAT | O_TRUNC,
				0600));
	if (temp_fd == -1)
	{
		perror("Error creating heredoc file");
		destroy_minishell(1);
	}
	handle_heredoc_input(temp_fd, delimiter);
	gc_close_fd(temp_fd);
	destroy_minishell(0);
}

static void	redirect_input_from_heredoc(void)
{
	int	temp_fd;

	temp_fd = gc_add_fd(open("heredoc_temp.txt", O_RDONLY));
	if (temp_fd == -1)
	{
		unlink("heredoc_temp.txt");
		perror("Error opening heredoc file for reading");
		destroy_minishell(1);
	}
	dup2(temp_fd, STDIN_FILENO);
	gc_close_fd(temp_fd);
	unlink("heredoc_temp.txt");
}

static int	handle_child_status(int status)
{
	t_shell	*shell;

	if (!WIFEXITED(status))
		return (0);
	if (WEXITSTATUS(status) == 130)
	{
		shell = get_shell();
		shell->exit_status = 130;
		shell->heredoc_failed = 1;
		return (pec("Heredoc process interrupted by SIGINT\n"));
	}
	if (WEXITSTATUS(status) != 0)
		return (pec("Heredoc process failed\n"));
	return (0);
}

bool	redirection_heredoc(const char *delimiter)
{
	pid_t	pid;
	int		status;

	pid = fork();
	reset_signals();
	if (pid == -1)
		destroy_minishell(pec("Fork failed"));
	if (pid == 0)
		create_heredoc_file(delimiter);
	waitpid(pid, &status, 0);
	reset_signals();
	if (handle_child_status(status) != 0)
		return (false);
	redirect_input_from_heredoc();
	return (true);
}
