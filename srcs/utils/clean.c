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

    // Free the command's path if allocated
    if ((*command)->path)
    {
        free((*command)->path);
        (*command)->path = NULL;
    }

    // Free the command's name if allocated
    if ((*command)->command_name)
    {
        free((*command)->command_name);
        (*command)->command_name = NULL;
    }

    // Free the concatenated argument string if allocated
    if ((*command)->argument)
    {
        free((*command)->argument);
        (*command)->argument = NULL;
    }

    // Free the redirect list if allocated
    if ((*command)->redirect)
    {
        ft_lstclear(&(*command)->redirect, free); // Adjust `free` based on your list's content type
        (*command)->redirect = NULL;
    }

    // Free the command structure itself
    free(*command);
    *command = NULL; // Prevent dangling pointers
}
