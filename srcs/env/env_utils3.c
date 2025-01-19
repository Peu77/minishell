/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:15:06 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 19:58:25 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**copy_env_to_string_array(void)
{
	t_list		*current;
	char		**env;
	int			i;
	char		*tmp;

	env = gc_malloc(sizeof(char *) * (ft_lstsize(get_shell()->env) + 1));
	if (!env)
		return (NULL);
	current = get_shell()->env;
	i = 0;
	while (current)
	{
		tmp = gc_add(ft_strjoin(((t_env_entry *)current->content)->key, "="));
		if (!tmp)
			return (free_string_array_at_index(env, i), NULL);
		env[i] = gc_add(ft_strjoin(tmp, ((t_env_entry *)current->content)->value));
		gc_free_ptr(tmp);
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

	entry = gc_malloc(sizeof(t_env_entry));
	if (!entry)
		return (pec(ERROR_MALLOC), false);
	new_node = ft_lstnew(entry);
	if (!new_node)
		return (free(entry), pec(ERROR_MALLOC), false);
	entry->key = gc_add(ft_strdup(key));
	entry->value = gc_add(ft_strdup(value));
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
		gc_free_ptr(entry->value);
		entry->value = gc_add(ft_strdup(value));
		if (!entry->value)
			return (pec(ERROR_MALLOC), false);
		return (true);
	}
	return (add_env_entry(key, value));
}
