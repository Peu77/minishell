#include "../../includes/minishell.h"
/*
void redirection_output(t_command *command, t_pipe *pipe)
{
    pipe->saved_stdout = dup(STDOUT_FILENO);
    if (pipe->saved_stdout == -1)
    {
        pev("dup failed for saving STDOUT");
        exit(EXIT_FAILURE);
    }
    int fd = open(command->redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        pev("open failed for redirection");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        pev("dup2 failed for redirection");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return;
}

void redirection_append(t_command *command, t_pipe *pipe)
{
	pipe->saved_stdout = dup(STDOUT_FILENO);
	if (pipe->saved_stdout == -1)
	{
		pev("dup failed for saving STDOUT");
		exit(EXIT_FAILURE);
	}
	int fd = open(command->redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		pev("open failed for redirection");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		pev("dup2 failed for redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void redirection_input(t_command *command, t_pipe *pipe)
{
	pipe->saved_stdout = dup(STDOUT_FILENO);
	if (pipe->saved_stdout == -1)
	{
		pev("dup failed for saving STDOUT");
		exit(EXIT_FAILURE);
	}
	int fd = open(command->redirection, O_RDONLY);
	if (fd == -1)
	{
		pev("open failed for input redirection");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		pev("dup2 failed for input redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void redirection_heredoc(const char *delimiter)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    int temp_fd;

    temp_fd = open("heredoc_temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (temp_fd == -1)
	{
        pev("Erreur lors de la création du fichier temporaire");
        exit(EXIT_FAILURE);
    }
    printf("heredoc> ");
    while ((nread = getline(&buffer, &bufsize, stdin)) != -1)
	{
        remove_newline(buffer);
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0)
            break;
        write(temp_fd, buffer, nread);
        write(temp_fd, "\n", 1);
        printf("heredoc> ");
    }
    free(buffer);
    close(temp_fd);
    temp_fd = open("heredoc_temp.txt", O_RDONLY);
    if (temp_fd == -1) {
        perror("Erreur lors de l'ouverture du fichier temporaire");
        exit(EXIT_FAILURE);
    }
    dup2(temp_fd, STDIN_FILENO);
    close(temp_fd);
    unlink("heredoc_temp.txt");
}
*/
