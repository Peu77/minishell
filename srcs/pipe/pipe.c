#include "../../includes/minishell.h"

void create_pipes(t_pipe *pip)
{
	pip->pipe_fd = malloc(pip->number_pipe * sizeof(int[2]));
	if (pip->pipe_fd == NULL)
	{
		perror("Failed to allocate memory for pipes");
		exit(EXIT_FAILURE);
	}
	int i = -1;
	while (++i < pip->number_pipe)
	{
		if (pipe(pip->pipe_fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void close_all_fds(t_pipe *pipe)
{
    int i = -1;

    while (++i < pipe->number_pipe)
    {
        close(pipe->pipe_fd[i][0]);
        close(pipe->pipe_fd[i][1]);
    }
    close(pipe->parent_pipe_fd[0]);
    close(pipe->parent_pipe_fd[1]);
}

void close_unused_pipes(t_pipe *pip)
{
    int i = -1;

    while (++i < pip->number_pipe)
    {
        if (i != pip->pipe_current_process - 1)
            close(pip->pipe_fd[i][0]);
        if (i != pip->pipe_current_process)
            close(pip->pipe_fd[i][1]);
    }
}

void create_parent_pipe(t_pipe *pip)
{
    int result = pipe(pip->parent_pipe_fd);
    while (result == -1)
	{
        perror("parent pipe");
        exit(EXIT_FAILURE);
    }
}

void child_process_execution(t_pipe *pipe, t_command *command, int i)
{
    if (command->redirection)
        redirection_monitor(command, pipe);

    if (i == 0)
        dup2(pipe->pipe_fd[i][1], STDOUT_FILENO);
    else if (i == pipe->number_command - 1)
        dup2(pipe->pipe_fd[i - 1][0], STDIN_FILENO);
    else 
    {
        dup2(pipe->pipe_fd[i - 1][0], STDIN_FILENO);
        dup2(pipe->pipe_fd[i][1], STDOUT_FILENO);
    }
    close_unused_pipes(pipe);
    close(pipe->parent_pipe_fd[0]);
    close(pipe->parent_pipe_fd[1]);
    execution_monitor(command, pipe);
    exit(EXIT_SUCCESS);
}

void parent_process_execution(t_pipe *pipe, int i)
{
    if (i > 0)
        close(pipe->pipe_fd[i - 1][0]);
    if (i < pipe->number_command - 1)
        close(pipe->pipe_fd[i][1]);
}

void prepare_execution(t_pipe *pipe, t_command *command, int i)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
        child_process_execution(pipe, command, i);
    else
        parent_process_execution(pipe, i);
    if (pipe->saved_stdout)
    {
        if (dup2(pipe->saved_stdout, STDOUT_FILENO) == -1)
            return (pev("dup2 restore STDOUT failed"), exit(EXIT_FAILURE));
		close(pipe->saved_stdout);
    }
    pipe->saved_stdout = 0;
}
