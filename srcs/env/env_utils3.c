/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:15:06 by eebert            #+#    #+#             */
/*   Updated: 2025/01/16 20:15:06 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char** copy_env_to_string_array() {
    t_list* current;
    t_env_entry* entry;
    char** env;
    int i;
    char* tmp;

    env = malloc(sizeof(char*) * (ft_lstsize(get_shell()->env) + 1));
    if (!env)
        return (NULL);
    current = get_shell()->env;
    i = 0;
    while (current) {
        entry = current->content;
        tmp = ft_strjoin(entry->key, "=");
        if (!tmp)
            return (free_string_array_at_index(env, i), NULL);
        env[i] = ft_strjoin(tmp, entry->value);
        free(tmp);
        if (!env[i])
            return (free_string_array_at_index(env, i), NULL);
        current = current->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}