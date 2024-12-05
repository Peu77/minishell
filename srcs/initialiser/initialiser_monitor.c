#include "../../includes/minishell.h"

int initialise_monitor(t_pipe **pipe, t_command **command, char *user_prompt, char **envp)
{
	initialise_pipe(pipe, user_prompt);
	if(!initialise_command(command, user_prompt, envp))
		pe(ERROR_INITIALISE);
	print_command_list(*command);
	return (1);
}
