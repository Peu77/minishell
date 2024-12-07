#include "../../includes/minishell.h"
#include <unistd.h>


int echo(t_command_test *command, bool is_n)
{
	if(!command->argument && !is_n)	
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (!is_n)
	{
		ft_putstr_fd(command->argument, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		ft_putstr_fd(command->argument, STDOUT_FILENO);
	return (1);
}
