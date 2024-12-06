#include "../../includes/minishell.h"

void pipe_monitor(t_pipe *pipe, t_command *command, char *user_prompt)
{
    if (!user_prompt || *user_prompt == '\0')
        return;
    if (!pipe)
    {
        pe("Failed to allocate memory for pipe structure");
        return;
    }
	if(pipe->number_command == 1)
	{
        execution_monitor(command, pipe);
		return ;
	}
    create_pipes(pipe);
    create_parent_pipe(pipe);

    int i = 0;
    while (i < pipe->number_command)
    {
        pipe->pipe_current_process = i + 1;
        prepare_execution(pipe, command, i);
        i++;
        command = command->next;
    }

    close(pipe->parent_pipe_fd[1]);
    i = 0;
    while (i < pipe->number_command)
    {
        wait(NULL);
        i++;
    }

    close(pipe->parent_pipe_fd[0]);
    close_unused_pipes(pipe);
}
