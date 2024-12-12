#include "../../includes/minishell.h"

void redirection_output(t_redirect *redirect)
{
    int fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        pev("open failed for output redirection");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        pev("dup2 failed for output redirection");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirection_append(t_redirect *redirect)
{
    int fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        pev("open failed for append redirection");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        pev("dup2 failed for append redirection");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirection_input(t_redirect *redirect)
{
    int fd = open(redirect->file, O_RDONLY);
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
