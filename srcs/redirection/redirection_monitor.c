#include "../../includes/minishell.h"


static void redirection_output(t_command *command, t_pipe *pipe)
{
    pipe->saved_stdout = dup(STDOUT_FILENO);
    if (pipe->saved_stdout == -1)
    {
        perror("dup failed for saving STDOUT");
        exit(EXIT_FAILURE);
    }

    // Open the file for redirection
    int fd = open(command->redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open failed for redirection");
        exit(EXIT_FAILURE);
    }

    // Redirect stdout to the file
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 failed for redirection");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    return;
}


void redirection_monitor(t_command *command, t_pipe *pipe)
{
	char redirection_token = '>';

	if (redirection_token == '>')
		redirection_output(command, pipe);
	
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

}
