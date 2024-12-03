#include "../../includes/minishell.h"

void redirection_monitor(t_command *command)
{
	char redirection_token = '>';

	if (redirection_token == '>')
	{
		int fd = open(command->redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open failed for redirection");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for redirection");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
	// a for apped( >>)
	else if (redirection_token == 'a')
	{
		
        int fd = open(command->redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open failed for redirection");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for redirection");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
	else if (redirection_token == '<')
    {
       int fd = open(command->redirection, O_RDONLY);
        if (fd == -1)
        {
            perror("open failed for input redirection");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 failed for input redirection");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
	//tobuil
	else if (redirection_token == 'h')
    {
       int fd = open(command->redirection, O_RDONLY);
        if (fd == -1)
        {
            perror("open failed for input redirection");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 failed for input redirection");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
    }

	return ;
}
