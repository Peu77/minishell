#include "../../includes/minishell.h"

void free_command(t_command **command)
{
    t_command *temp;

    if (!command || !*command)
        return;

    while (*command)
    {
        temp = (*command)->next;
        free(*command);
        *command = temp;
    }
}

static void close_fd(t_pipe *pipe_struct)
{
	int i = 0;

	printf("closing ..%d \n", pipe_struct->number_command);

	if (pipe_struct->pipe_fd)
	{
		while (i < pipe_struct->number_command++)
		{
			if (pipe_struct->pipe_fd[i][0] >= 0)
			{
				close(pipe_struct->pipe_fd[i][0]);
				pipe_struct->pipe_fd[i][0] = -1; 
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
}

void	exit_shell(t_pipe *pipe, int exno)
{
	close_fd(pipe);
	free(pipe);
	exit(exno);
}

void remove_newline(char *buffer) 
{
    size_t len = ft_strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}
