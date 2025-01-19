/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:25 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/19 18:17:23 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			free(buffer);
			break ;
		}
		write(temp_fd, buffer, ft_strlen(buffer));
		write(temp_fd, "\n", 1);
		free(buffer);
	}
}

static void	create_heredoc_file(const char *delimiter, t_command *command,
		t_parenthesis_fd *parenthesis_fd)
{
	int	temp_fd;


	signal(SIGINT, heredoc_sighandler);
	temp_fd = open("heredoc_temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (temp_fd == -1)
	{
		perror("Error creating heredoc file");
		exit(1);
	}
	handle_heredoc_input(temp_fd, delimiter, command, parenthesis_fd);
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

int	redirection_heredoc(const char *delimiter, t_command *command,
		t_parenthesis_fd *parenthesis_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	reset_signals();
	if (pid == -1)
		exit(pec("Fork failed"));
	if (pid == 0)
		create_heredoc_file(delimiter, command, parenthesis_fd);
	else
	{
		waitpid(pid, &status, 0);
		main_signals();
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				return (pec("Heredoc process failed\n"));
		}
		else
			return (pec("Heredoc process terminated abnormally\n"));
	}
	redirect_input_from_heredoc();
	return (0);
}
