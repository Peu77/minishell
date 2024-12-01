#include "../../includes/minishell.h"
#include <unistd.h>


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
		execution_monitor(command);
		/*
        char **arguments = ft_split(command->argument, ' ');
        if (command->path == NULL)
        {
            printf("Command %s not found\n", command->command_name);
            exit(EXIT_FAILURE);
        }
        else if (execve(command->path, arguments, NULL) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
		*/
    }
}
void pipe_monitor(char *user_prompt)
{
    t_pipe *pipe = malloc(sizeof(t_pipe));
    t_command *command = NULL;

    if (!user_prompt || *user_prompt == '\0')
        return;
    if (!pipe)
    {
        perror("Failed to allocate memory for pipe structure");
        return;
    }

    initialise_pipe(&pipe, &command, user_prompt);
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


    // Parent process
    close(pipe->parent_pipe_fd[1]);

    // Wait for all children to finish
    i = 0;
    while (i < pipe->number_command)
    {
        wait(NULL);
        i++;
    }

    // Close parent pipe's reading end
    close(pipe->parent_pipe_fd[0]);
    close_unused_pipes(pipe);

    // Free allocated memory
    free(pipe->pipe_fd);
    free(pipe);
}
