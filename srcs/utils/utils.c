#include "../../includes/minishell.h"


void free_command_split(char **command_split)
{
    int i = 0;

    if (!command_split)
        return;

    while (command_split[i])
    {
        free(command_split[i]); // Free each string
        command_split[i] = NULL; // Reset pointer after freeing
        i++;
    }

    free(command_split); // Free the array itself
    command_split = NULL; // Reset pointer after freeing
}
void free_command(t_command **command)
{
    t_command *temp;

    if (!command || !*command)
        return;

    while (*command)
    {
        temp = (*command)->next;
		if((*command)->command_split)
		{
			if ((*command)->command_split)
            free_command_split((*command)->command_split);
		}
        free(*command);
        *command = temp;
    }
}

void free_pipe(t_pipe **pipe)
{
	if(!pipe || !*pipe)
		return;
	free(pipe);
}

int free_all(t_pipe **pipe, t_command **command)
{
	free_pipe(pipe);
	free_command(command);
	return (1);
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
