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

int free_export_command(t_export *export_list)
{
    if (export_list->args)
    {
        free_command_split(export_list->args); 
        export_list->args = NULL;
    }
    if (export_list->variable_name)
    {
        free(export_list->variable_name);
        export_list->variable_name = NULL;
    }
    if (export_list->variable_value)
    {
        free(export_list->variable_value);
        export_list->variable_value = NULL;
    }
    return 1;
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
