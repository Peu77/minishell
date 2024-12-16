#include "../../includes/minishell.h"

int ft_clear(void)
{
    write(1, "\033[H\033[2J", 7);
	return (1);
}
