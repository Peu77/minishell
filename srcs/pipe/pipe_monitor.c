#include "../../includes/minishell.h"


void execute_no_pipe(t_command *command, t_pipe *pipe)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if (command->redirection)
            redirection_monitor(command, pipe);
        execution_monitor(command, pipe);
    }
    else
        (wait(NULL));
}


void execute_with_pipes(t_pipe *pipe, t_command *command)
{
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


int pipe_monitor(t_pipe *pipe, t_command *command, char *user_prompt)
{
    if (!user_prompt || *user_prompt == '\0')
        pe("empty user prompt");
    if (!pipe)
        pe("Failed to allocate memory for pipe structure");
	if(pipe->number_command == 1)
        execute_no_pipe(command, pipe);
	else
		execute_with_pipes(pipe, command);
	return 1;
}

