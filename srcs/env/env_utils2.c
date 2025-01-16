/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:42:14 by eebert            #+#    #+#             */
/*   Updated: 2025/01/16 22:50:50 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "../../includes/minishell.h"

void split_env_pairstr(const char* pair_str, char* key, char* value) {
	int i;
	int j;

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

bool add_env_pairstr(const char* pair_str) {
	char key[MAX_VAR_LEN];
	char value[MAX_VAR_LEN];

	split_env_pairstr(pair_str, key, value);
	return add_env_entry(key, value);
}

char	*get_env_value(const char *key)
{
	t_env_entry	*entry;

	entry = get_env_entry(key);
	if(!entry)
		return NULL;
	return entry->value;
}

t_env_entry* get_env_entry(const char* key) {
	t_list* current;

	current = get_shell()->env;
	while (current) {
		if (ft_strlen(((t_env_entry*)current->content)->key) == ft_strlen(key) &&
			ft_strncmp(((t_env_entry*)current->content)->key, key, ft_strlen(key)) == 0) {
			return current->content;
		}
		current = current->next;
	}
	return NULL;
}

void free_env_entry(void* content) {
	t_env_entry* entry;

	entry = content;
	free(entry->key);
	free(entry->value);
	free(entry);
}

bool add_env_entry(const char* key, const char* value) {
	t_env_entry* entry;
	t_list* new_node;

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

bool set_env_value(const char *key,const char *value)
{
	t_env_entry* entry;

	if(!key || !value)
		return false;
	entry = get_env_entry(key);
	if(entry) {
		free(entry->value);
		entry->value = ft_strdup(value);
		if(!entry->value)
			return (pec(ERROR_MALLOC), false);
		return true;
	}
	return add_env_entry(key, value);
}
