#include "../../includes/minishell.h"


void redirection_monitor(t_command *command, t_pipe *pipe)
{
	char redirection_token = 'a';

	if (redirection_token == '>')
		redirection_output(command, pipe);
	
	// a for apped( >>)
	else if (redirection_token == 'a')
			redirection_append(command, pipe);
	else if (redirection_token == '<')
			redirection_output(command, pipe);
	//tobuild
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
