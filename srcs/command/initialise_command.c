/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/14 20:22:15 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        new_node = ft_lstnew(original->content);
        if (!new_node)
        {
            ft_lstclear(&copy, free);
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
        return pe(ERROR_MALLOC);
    (*command)->saved_stdout = 0;
    return 1;
}



int transform_node_to_command(char *value, t_command_test **command, t_list *redirection)
{
    char **arg;

    *command = malloc(sizeof(t_command_test));
    if (!(*command))
        return pe(ERROR_MALLOC);
    ft_memset(*command, 0, sizeof(t_command_test));

    arg = ft_split(value, ' ');
    if (!arg)
    {
        free(*command);
        return pe(ERROR_SPLIT);
    }
    (*command)->command_name = ft_strdup(arg[0]);
    if (!(*command)->command_name)
    {
        free_command_split(arg);
        free(*command);
        return pe(ERROR_MALLOC);
    }
    if (!arg[1])
        (*command)->argument = NULL;
    else
    {
        if (concatenate_arguments(arg, &((*command)->argument)) != 1)
        {
            free_command_split(arg);
            free((*command)->command_name);
            free(*command);
            return pe(ERROR_MALLOC);
        }
    }
    get_path(command);
    if (redirection)
        get_redirection(command, redirection);
    free_command_split(arg);
    if ((*command)->argument)
    {
        free((*command)->argument);
    }

    return 1;
}
