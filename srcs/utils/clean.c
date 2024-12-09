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




void free_command(t_command_test **command)
{
    if (!command || !*command)
        return;
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
    if ((*command)->redirect)
    {
        ft_lstclear(&(*command)->redirect, free);
        (*command)->redirect = NULL;
    }
    free(*command);
    *command = NULL;
}
