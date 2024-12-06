#include "../../includes/minishell.h"

void create_pipes(t_pipe *pip)
{
	pip->pipe_fd = malloc(pip->number_pipe * sizeof(int[2]));
	if (pip->pipe_fd == NULL)
	{
		perror("Failed to allocate memory for pipes");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while (i < pip->number_pipe)
	{
		if (pipe(pip->pipe_fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}


void close_unused_pipes(t_pipe *pip)
{
	int i = 0;

	while (i < pip->number_pipe) 
	{
		if (pip->pipe_current_process== 0) 
		{ 
			close(pip->pipe_fd[i][0]);
			close(pip->pipe_fd[i][1]);
		} 
		else
	{  
			if (i != pip->pipe_current_process - 1)
				close(pip->pipe_fd[i][0]);
			if (i != pip->pipe_current_process)
				close(pip->pipe_fd[i][1]);
		}
		i++;
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

void prepare_execution(t_pipe *pipe, t_command *command, int i)
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
		if (i == 0) 
		{
			dup2(pipe->pipe_fd[i][1], STDOUT_FILENO);
		}
		else if (i == pipe->number_command - 1)
		{
			dup2(pipe->pipe_fd[i - 1][0], STDIN_FILENO);
		}
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
    else
    {
        if (i > 0)
            close(pipe->pipe_fd[i - 1][0]);

        if (i < pipe->number_command - 1) 
            close(pipe->pipe_fd[i][1]);
    }
		if(pipe->saved_stdout)
		{
			if (dup2(pipe->saved_stdout, STDOUT_FILENO) == -1)
        	{
            	perror("dup2 restore STDOUT failed");
            	exit(EXIT_FAILURE);
        	}
		}
}
