#include "../../includes/minishell.h"



void free_command_split(char **command_split)
{
    int i = 0;

    if (!command_split)
        return;

    while (command_split[i])
    {
        free(command_split[i]);
        i++;
    }
    free(command_split);
}


void free_command(t_command **command)
{
    t_command *temp;

    if (!command || !*command)
        return;

    while (*command)
    {
        temp = (*command)->next;
        if ((*command)->path)
        {
            free((*command)->path);
            (*command)->path = NULL;
        }
        if ((*command)->command_name)
        {
            free((*command)->command_name);
            (*command)->command_name = NULL;
        }
        if ((*command)->argument)
        {
            free((*command)->argument);
            (*command)->argument = NULL;
        }
        free(*command);
        *command = temp;
    }
}

void free_pipe(t_pipe **pipe)
{
    if (!pipe || !*pipe)
        return;

    free(*pipe);
    *pipe = NULL; // Avoid dangling pointer
}

int free_all(t_pipe **pipe, t_command **command)
{
	free_pipe(pipe);
	free_command(command);
	return (1);
}
