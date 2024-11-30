#include "../../includes/minishell.h"

static void free_command(char **command)
{
    int i = 0;
    while (command[i])
    {
        free(command[i]);
        i++;
    }
    free(command);
}

void execution_command(t_command *command_list)
{
    char **command = ft_split(command_list->command, ' ');

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        free_command(command);
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
		if (execve(command_list->path, command, NULL) == -1)
        {
            perror("execve failed");
            free_command(command);
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        wait(NULL);
        free_command(command);
    }
}

void execute_two_pipes(t_command *cmd1, t_command *cmd2)
{
    int pipe_fd[2];
    pid_t pid1;
	pid_t pid2;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        pe("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        char **command1 = ft_split(cmd1->command, ' ');
        if (execve(cmd1->path, command1, NULL) == -1)
        {
            pe("execve cmd1 failed");
            free_command(command1);
            exit(EXIT_FAILURE);
        }
    }
    pid2 = fork();
    if (pid2 == -1)
    {
        pe("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0)
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);

        char **command2 = ft_split(cmd2->command, ' ');
        if (execve(cmd2->path, command2, NULL) == -1)
        {
            pe("execve cmd2 failed");
            free_command(command2);
            exit(EXIT_FAILURE);
        }
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

