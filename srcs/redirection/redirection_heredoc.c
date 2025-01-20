/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:44:20 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 21:12:39 by ftapponn         ###   ########.fr       */
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

/*
static void	cleanup_and_exit(int temp_fd, t_command *command,
		t_parenthesis_fd *parenthesis_fd)
{
	close(temp_fd);
	if (command)
	{
		close(command->saved_stdin);
		close(command->saved_stdout);
	}
	if (parenthesis_fd)
	{
		close(parenthesis_fd->fd_backup_stdin);
		close(parenthesis_fd->fd_backup_stdout);
	}
	unlink("heredoc_temp.txt");
	exit(1);
}
*/
/*
static void	handle_heredoc_input(int temp_fd, const char *delimiter,
		t_command *command, t_parenthesis_fd *parenthesis_fd)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (buffer == NULL)
			cleanup_and_exit(temp_fd, command, parenthesis_fd);
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0)
		{
			gc_free_ptr(buffer);
			break ;
		}
		write(temp_fd, buffer, ft_strlen(buffer));
		write(temp_fd, "\n", 1);
		free(buffer);
	}
}
*/

static void	handle_heredoc_input(int temp_fd, const char *delimiter)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (buffer == NULL)
		{
			write(temp_fd, "\n", 1);
			break ;
		}
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(buffer);
			break ;
		}
		write(temp_fd, buffer, ft_strlen(buffer));
		write(temp_fd, "\n", 1);
		free(buffer);
	}
}

static void	create_heredoc_file(const char *delimiter)
{
	int	temp_fd;

	signal(SIGINT, heredoc_sighandler);
	temp_fd = open("heredoc_temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (temp_fd == -1)
	{
		perror("Error creating heredoc file");
		exit(1);
	}
	handle_heredoc_input(temp_fd, delimiter);
	close(temp_fd);
	exit(0);
}

static void	redirect_input_from_heredoc(void)
{
	int	temp_fd;

	temp_fd = open("heredoc_temp.txt", O_RDONLY);
	if (temp_fd == -1)
	{
		unlink("heredoc_temp.txt");
		perror("Error opening heredoc file for reading");
		exit(1);
	}
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
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

int	redirection_heredoc(const char *delimiter)
{
	pid_t	pid;
	int		status;

	pid = fork();
	reset_signals();
	if (pid == -1)
		exit(pec("Fork failed"));
	if (pid == 0)
		create_heredoc_file(delimiter);
	waitpid(pid, &status, 0);
	reset_signals();
	if (handle_child_status(status) != 0)
		return (1);
	redirect_input_from_heredoc();
	return (0);
}
