#include "../../includes/minishell.h"

static void close_fd(t_pipe *pipe_struct)
{
    int i = 0;

	printf("closing ..%d \n", pipe_struct->number_command);
    // Fermer les file descriptors dans pipe_fd
    if (pipe_struct->pipe_fd)
    {
        while (i < pipe_struct->number_command++)
        {
            if (pipe_struct->pipe_fd[i][0] >= 0)
            {
                close(pipe_struct->pipe_fd[i][0]);
                pipe_struct->pipe_fd[i][0] = -1; // Éviter de refermer
            }
            if (pipe_struct->pipe_fd[i][1] >= 0)
            {
                close(pipe_struct->pipe_fd[i][1]);
                pipe_struct->pipe_fd[i][1] = -1;
            }
            i++;
		  if (pipe_struct->parent_pipe_fd[0] >= 0)
    	{
    	    close(pipe_struct->parent_pipe_fd[0]);
    	    pipe_struct->parent_pipe_fd[0] = -1;
    	}
    	if (pipe_struct->parent_pipe_fd[1] >= 0)
    	{
    	    close(pipe_struct->parent_pipe_fd[1]);
    	    pipe_struct->parent_pipe_fd[1] = -1;
    	}
        }
    }
    // Fermer les file descriptors dans parent_pipe_fd
}

void	exit_shell(t_pipe *pipe, int exno)
{
	close_fd(pipe);
	free(pipe);
	exit(exno);
}


