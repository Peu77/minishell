#include "../../includes/minishell.h"

void print_command(t_command_test *command)
{
	printf("\n STRUCT COMMAND : \n ");
    if (!command)
    {
        printf("Command is NULL.\n");
        return;
    }
    printf("Command Name: %s\n", command->command_name ? command->command_name : "(NULL)");
    printf("Arguments: %s\n", command->argument ? command->argument : "(NULL)");
    printf("Paths: %s\n", command->path ? command->path : "(NULL)");
}

int concatenate_arguments(char **arg, char **result)
{
    int i = 0;
    size_t total_length = 0;

    while (arg[++i])
        total_length += ft_strlen(arg[i]) + 1;
    *result = malloc(total_length);
    if (!(*result))
        return pe(ERROR_MALLOC);
    (*result)[0] = '\0';
    i = 0;
    while (arg[++i])
    {
        ft_strlcat(*result, arg[i], total_length);
        if (arg[i + 1])
            ft_strlcat(*result, " ", total_length);
    }
    return (1);
}

t_list *duplicate_list(t_list *original)
{
    t_list *copy = NULL;
    t_list *new_node;
    while (original)
    {
        new_node = ft_lstnew(original->content); // Adjust based on your `t_list` implementation
        if (!new_node)
        {
            ft_lstclear(&copy, free); // Free any nodes already allocated
            return NULL;
        }
        ft_lstadd_back(&copy, new_node);
        original = original->next;
    }
    return copy;
}
int get_redirection(t_command_test **command, t_list *redirection)
{
    (*command)->redirect = duplicate_list(redirection);
    if (!(*command)->redirect)
        return pe(ERROR_MALLOC); // Handle allocation failure
    (*command)->saved_stdout = 0;
    return 1;
}

int transform_node_to_command(char *value, t_command_test **command, t_list *redirection, char **envp)
{
    char **arg;

	*command = malloc(sizeof(t_command_test));
	if (!(*command))
 	   return pe(ERROR_MALLOC);
	ft_memset(*command, 0, sizeof(t_command_test));
    if (!(*command))
        return pe(ERROR_MALLOC);
    arg = ft_split(value, ' ');
    if (!arg)
        return pe(ERROR_SPLIT);
    (*command)->command_name = ft_strdup(arg[0]);
    if (!arg[1])
        (*command)->argument = NULL;
    else
    {
        if (concatenate_arguments(arg, &((*command)->argument)) != 1)
        {
            free(arg);
            return pe(ERROR_MALLOC);
        }
    }
	get_path(command);
	(*command)->envp = envp;
	if(redirection)
		get_redirection(command, redirection);
    free_command_split(arg);
    return (1);
}
