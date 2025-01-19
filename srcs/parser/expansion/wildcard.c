/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:04:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 19:59:13 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <parse.h>
#include <stdbool.h>

static bool	is_match(const char *pattern, size_t pattern_len, const char *str, const size_t pattern_i)
{
	if (pattern_len == 0)
	{
		return (*str == '\0');
	}
	if (*pattern == '*' && !is_escaped(pattern, pattern_i))
	{
		if (is_match(pattern + 1, pattern_len - 1, str, pattern_i + 1))
			return (true);
		if (*str && is_match(pattern, pattern_len, str + 1, pattern_i))
			return (true);
	}
	if (*str && (*pattern == *str || (*pattern == '?' && !is_escaped(pattern, pattern_i))))
	{
		return (is_match(pattern + 1, pattern_len - 1, str + 1, pattern_i));
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
		if (is_match(pattern, ft_strlen(pattern), (*files.list)->content, 0)
			&& !((*(char *)(*files.list)->content) == '.' && *pattern != '.'))
		{
			if (files.count > 1)
				tmp_str = gc_add(ft_strjoin((*files.list)->content, " "));
			else
				tmp_str = gc_add(ft_strdup((*files.list)->content));
			if (!tmp_str)
				return (pe("gc_malloc failed"), false);
			new_node = ft_lstnew(tmp_str);
			if (!new_node)
				return (pe("gc_malloc failed"), gc_free_ptr(tmp_str), false);
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
		return (gc_list_clear(&files, gc_free_ptr), false);
	expanded_pattern = expand_env_vars(old_pattern, pattern_len);
	if (!expanded_pattern)
		return (-1);
	matches = 0;
	if (!match_files(expanded_pattern, (t_list_data){&files, file_count}, list,
		&matches))
		return (gc_list_clear(&files, gc_free_ptr), false);
	if (matches == 0)
	{
		ft_lstadd_back(list, ft_lstnew(expanded_pattern));
		*get_char_count() += ft_strlen(expanded_pattern);
	}
	else
		gc_free_ptr(expanded_pattern);
	return (gc_list_clear(&files, gc_free_ptr), true);
}

int	get_wildcard_len(const char *str)
{
	int		i;
	bool	found_wildcard;

	i = 0;
	found_wildcard = false;
	while (str[i] && !is_wildcard_separator(str[i]))
	{
		if (str[i] == '*')
			found_wildcard = true;
		i++;
	}
	if (!found_wildcard)
		return (0);
	return (i);
}

char* expand_wildcards(const char *str)
{
	size_t		i;
	int		wildcard_len;
	*get_char_count() = 0;
	t_list	*list;

	i = 0;
	list = NULL;
	while (str[i])
	{
		if(skip_safe_quotes(str, &i, &list))
			continue;
		wildcard_len = get_wildcard_len(str + i);
		if (wildcard_len > 0)
			{
				if (!expand_wildcard(str + i, wildcard_len, &list))
					return (false);
				i += wildcard_len;
				continue;
			}
		if (!add_str_to_result(str, &i, &list, 1))
			return (gc_list_clear(&list, gc_free_ptr), NULL);
	}
	return (strlst_to_str(list));
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
	gc_list_clear(&list, free);

	return (0);
}
*/
