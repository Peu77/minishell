/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:25 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 18:50:22 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_heredoc_file(const char *delimiter)
{
	char	*buffer;
	int		temp_fd;

	// signal(SIGINT, heredoc_sighandler);
	buffer = NULL;
	temp_fd = open("heredoc_temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (temp_fd == -1)
		exit(pec(ERROR_HEREDOC));
	while (1)
	{
		buffer = readline("heredoc> ");
		if (buffer == NULL)
		{
			close(temp_fd);
			unlink("heredoc_temp.txt");
			exit(pec(ERROR_HEREDOC_SIGNAL));
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
	close(temp_fd);
	// main_signals();
}

void	redirect_input_from_heredoc(void)
{
	int	temp_fd;

	temp_fd = open("heredoc_temp.txt", O_RDONLY);
	if (temp_fd == -1)
	{
		unlink("heredoc_temp.txt");
		exit(pec(ERROR_HEREDOC));
	}
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	unlink("heredoc_temp.txt");
}

void	redirection_heredoc(const char *delimiter)
{
	create_heredoc_file(delimiter);
	redirect_input_from_heredoc();
}
