/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:23 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/13 21:10:25 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void split_variable(char *line, char **name, char **value)
{
    char *equal_pos = strchr(line, '=');
    if (equal_pos)
    {
        *name = ft_strndup(line, equal_pos - line);
        *value = ft_strdup(equal_pos + 1);
    }
}

t_env *initialise_env(char **env)
{
    t_env *head = NULL;
    t_env *tail = NULL;
    t_env *new_node = NULL;
    char *name = NULL;
    char *value = NULL;
    int i = -1;

    while (env[++i] != NULL)
    {
        split_variable(env[i], &name, &value);
        new_node = (t_env *)malloc(sizeof(t_env));
        if (!new_node)
            return NULL;
        new_node->variable_name = name;
        new_node->variable_value = value;
        new_node->next = NULL;
        new_node->previous = tail;
        if (tail)
            tail->next = new_node;
        tail = new_node;
        if (!head)
            head = new_node;
    }
    return head;
}
