/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:38:14 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 14:05:33 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <libft.h>
#include <minishell.h>
#include <stdbool.h>

bool	is_wildcard_separator(const char c)
{
	return (ft_isspace(c) || c == '\'' || c == '\"');
}

bool	get_files_in_dir(const char *path, t_list **list, size_t *amount)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*new_node;
	char			*file_name_cpy;

	dir = opendir(path);
	if (dir == NULL)
		return (pe("Error: Unable to open directory"), false);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		(*amount)++;
		file_name_cpy = gc_add(ft_strdup(entry->d_name));
		if (!file_name_cpy)
			return (pe("gc_malloc failed"), false);
		new_node = ft_lstnew(file_name_cpy);
		if (!new_node)
			return (gc_free_ptr(file_name_cpy), pe("malloc failed"), false);
		ft_lstadd_back(list, new_node);
	}
	return (closedir(dir), true);
}
