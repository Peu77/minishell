#include "../../includes/minishell.h"

int pe(const char *message)
{
    write(STDERR_FILENO, RED, ft_strlen(RED));
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, RESET, ft_strlen(RESET));
    write(STDERR_FILENO, "\n", 1);
	return (0);
}

void pev(const char *message)
{
    write(STDERR_FILENO, RED, ft_strlen(RED));
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, RESET, ft_strlen(RESET));
    write(STDERR_FILENO, "\n", 1);
}
