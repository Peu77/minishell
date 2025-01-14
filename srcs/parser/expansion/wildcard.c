/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:04:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 14:10:42 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <parse.h>
#include <stdbool.h>

static bool	is_match(const char *pattern, int pattern_len, const char *str)
{
	if (pattern_len == 0)
	{
		return (*str == '\0');
	}
	if (*pattern == '*')
	{
		if (is_match(pattern + 1, pattern_len - 1, str))
			return (true);
		if (*str && is_match(pattern, pattern_len, str + 1))
			return (true);
	}
	if (*str && (*pattern == *str || *pattern == '?'))
	{
		return (is_match(pattern + 1, pattern_len - 1, str + 1));
	}
	return (false);
}

static bool	match_files(const char *pattern, t_list_data files,
		t_list **matches, size_t *matches_count)
{
	char	*tmp_str;
	t_list	*new_node;

	while (*files.list)
	{
		if (is_match(pattern, ft_strlen(pattern), (*files.list)->content)
			&& (*(char *)(*files.list)->content) != '.' && *pattern != '.')
		{
			if (files.count > 1)
				tmp_str = ft_strjoin((*files.list)->content, " ");
			else
				tmp_str = ft_strdup((*files.list)->content);
			if (!tmp_str)
				return (pe("malloc failed"), false);
			new_node = ft_lstnew(tmp_str);
			if (!new_node)
				return (pe("malloc failed"), free(tmp_str), false);
			ft_lstadd_back(matches, new_node);
			*get_char_count() += ft_strlen(tmp_str);
			(*matches_count)++;
		}
		files.count--;
		files.list = &(*files.list)->next;
	}
	return (true);
}

bool	expand_wildcard(const char *old_pattern, size_t pattern_len,
		t_list **list)
{
	size_t	matches;
	t_list	*files;
	size_t	file_count;
	char	*expanded_pattern;

	files = NULL;
	file_count = 0;
	if (!get_files_in_dir(".", &files, &file_count))
		return (ft_lstclear(&files, free), false);
	expanded_pattern = expand_env_vars(old_pattern, pattern_len);
	if (!expanded_pattern)
		return (-1);
	matches = 0;
	if (!match_files(expanded_pattern, (t_list_data){&files, file_count}, list,
		&matches))
		return (ft_lstclear(&files, free), false);
	if (matches == 0)
	{
		ft_lstadd_back(list, ft_lstnew(expanded_pattern));
		*get_char_count() += ft_strlen(expanded_pattern);
	}
	else
		free(expanded_pattern);
	return (ft_lstclear(&files, free), true);
}

int	get_wildcard_len(char *str)
{
	int		i;
	bool	found_wildcard;

	i = 0;
	found_wildcard = false;
	while (str[i] && !is_wildcard_separator(str[i]))
	{
		if (str[i] == '*' || str[i] == '?')
			found_wildcard = true;
		i++;
	}
	if (!found_wildcard)
		return (0);
	return (i);
}

/*
int	main(void) {
	char *str = "*";
	t_list *list = NULL;
	int char_count = 0;
	expand_wildcard(str, &list, &char_count);
	t_list *tmp = list;
	while (1) {
		if(tmp == NULL) break ;

		printf("%s", (char*)tmp->content);

		tmp = tmp->next;
	}
	ft_lstclear(&list, free);

	return (0);
}
*/
