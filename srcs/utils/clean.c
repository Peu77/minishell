#include "../../includes/minishell.h"

void free_command_split(char **command_split)
{
    int i = 0;

    if (!command_split)
        return;

    while (command_split[i])
    {
        free(command_split[i]);
        command_split[i] = NULL;
        i++;
    }
    free(command_split);
    command_split = NULL;
}

void free_command(t_command **command)
{
    t_command *temp;

    if (!command || !*command)
        return;

    while (*command)
    {
        temp = (*command)->next;
		if((*command)->command_split)
		{
			if ((*command)->command_split)
            free_command_split((*command)->command_split);
		}
        free(*command);
        *command = temp;
    }
}

void free_pipe(t_pipe **pipe)
{
	if(!pipe || !*pipe)
		return;
	free(pipe);
}

int free_all(t_pipe **pipe, t_command **command)
{
	free_pipe(pipe);
	free_command(command);
	return (1);
}
