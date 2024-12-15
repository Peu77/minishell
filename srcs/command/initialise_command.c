/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 12:11:54 by ftapponn         ###   ########.fr       */
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

t_env *get_env(t_env *original_env)
{
    t_env *new_head = NULL;
    t_env *new_tail = NULL;
    t_env *new_node = NULL;

    while (original_env)
    {
        new_node = (t_env *)malloc(sizeof(t_env));
        if (!new_node)
        {
            // Free the new list in case of allocation failure
            while (new_head)
            {
                t_env *tmp = new_head;
                new_head = new_head->next;
                free(tmp->variable_name);
                free(tmp->variable_value);
                free(tmp);
            }
            return NULL;
        }
        new_node->variable_name = ft_strdup(original_env->variable_name);
        new_node->variable_value = ft_strdup(original_env->variable_value);
        new_node->next = NULL;
        new_node->previous = new_tail;

        if (new_tail)
            new_tail->next = new_node;

        new_tail = new_node;
        if (!new_head)
            new_head = new_node;

        original_env = original_env->next;
    }
    return new_head;
}

int transform_node_to_command(char *value, t_command_test **command, t_list *redirection, t_env *env)
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
    (*command)->env = get_env(env);
    if (redirection)
        get_redirection(command, redirection);
    free_command_split(arg);
    if ((*command)->argument)
    {
        free((*command)->argument);
    }

    return 1;
}
