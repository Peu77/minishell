/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:42:14 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 16:16:02 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_env_pairstr(const char *pair_str, char *key, char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pair_str[i] != '=')
	{
		key[i] = pair_str[i];
		i++;
	}
	key[i] = '\0';
	i++;
	while (pair_str[i] != '\0')
	{
		value[j++] = pair_str[i];
		i++;
	}
	value[j] = '\0';
}

bool	add_env_pairstr(const char *pair_str)
{
	char	key[MAX_VAR_LEN];
	char	value[MAX_VAR_LEN];

	split_env_pairstr(pair_str, key, value);
	return (add_env_entry(key, value));
}

char	*get_env_value(const char *key)
{
	t_env_entry	*entry;

	entry = get_env_entry(key);
	if (!entry)
		return (NULL);
	return (entry->value);
}

t_env_entry	*get_env_entry(const char *key)
{
	t_list	*current;

	current = get_shell()->env;
	while (current)
	{
		if (ft_strlen(((t_env_entry *)current->content)->key) == ft_strlen(key)
			&& ft_strncmp(((t_env_entry *)current->content)->key, key,
				ft_strlen(key)) == 0)
		{
			return (current->content);
		}
		current = current->next;
	}
	return (NULL);
}

void	free_env_entry(void *content)
{
	t_env_entry	*entry;

	entry = content;
	gc_free_ptr(entry->key);
	gc_free_ptr(entry->value);
	gc_free_ptr(entry);
}
