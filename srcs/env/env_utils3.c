/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:15:06 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 16:39:15 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**copy_env_to_string_array(void)
{
	t_list		*current;
	t_env_entry	*entry;
	char		**env;
	int			i;
	char		*tmp;

	(void)entry;
	env = malloc(sizeof(char *) * (ft_lstsize(get_shell()->env) + 1));
	if (!env)
		return (NULL);
	current = get_shell()->env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(((t_env_entry *)current->content)->key, "=");
		if (!tmp)
			return (free_string_array_at_index(env, i), NULL);
		env[i] = ft_strjoin(tmp, ((t_env_entry *)current->content)->value);
		free(tmp);
		if (!env[i])
			return (free_string_array_at_index(env, i), NULL);
		current = current->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

bool	add_env_entry(const char *key, const char *value)
{
	t_env_entry	*entry;
	t_list		*new_node;

	entry = malloc(sizeof(t_env_entry));
	if (!entry)
		return (pec(ERROR_MALLOC), false);
	new_node = ft_lstnew(entry);
	if (!new_node)
		return (free(entry), pec(ERROR_MALLOC), false);
	entry->key = ft_strdup(key);
	entry->value = ft_strdup(value);
	if (!entry->key || !entry->value)
		return (pec(ERROR_MALLOC), free_env_entry(entry), false);
	return (ft_lstadd_back(&get_shell()->env, new_node), true);
}

bool	set_env_value(const char *key, const char *value)
{
	t_env_entry	*entry;

	if (!key || !value)
		return (false);
	entry = get_env_entry(key);
	if (entry)
	{
		free(entry->value);
		entry->value = ft_strdup(value);
		if (!entry->value)
			return (pec(ERROR_MALLOC), false);
		return (true);
	}
	return (add_env_entry(key, value));
}
