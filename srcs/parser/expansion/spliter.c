/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:54:42 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 15:09:38 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gcollector.h>
#include <libft.h>
#include <parse.h>
#include <stdbool.h>
#include <stdlib.h>

static bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static bool	matches_quote(char c, char quote_type)
{
	return (c == quote_type);
}

static bool	get_word_length_helper(const char *str, bool *in_quotes,
		char *quote_type, size_t *len)
{
	if (is_quote(str[*len]) && !*in_quotes && !is_escaped(str, *len))
	{
		*in_quotes = true;
		*quote_type = str[*len];
	}
	else if (matches_quote(str[*len], *quote_type) && *in_quotes
		&& !is_escaped(str, *len))
	{
		(*len)++;
		(*in_quotes) = false;
		*quote_type = 0;
		if (!str[*len] || (ft_isspace(str[*len]) && !*in_quotes))
			return (false);
		return (true);
	}
	if (ft_isspace(str[*len]) && !*in_quotes && !is_escaped(str, *len))
		return (false);
	(*len)++;
	return (true);
}

static size_t	get_word_length(char const *str)
{
	size_t	len;
	bool	in_quotes;
	char	quote_type;

	len = 0;
	in_quotes = false;
	quote_type = 0;
	while (str[len])
	{
		if (!get_word_length_helper(str, &in_quotes, &quote_type, &len))
			break ;
	}
	return (len);
}

char	**split_quotes(char const *str)
{
	char	**result;
	size_t	word_count;
	size_t	i;
	size_t	word_len;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	result = gc_malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (ft_isspace(*str))
			str++;
		word_len = get_word_length(str);
		result[i] = extract_word(str, word_len);
		str += word_len;
		i++;
	}
	result[i] = NULL;
	return (result);
}
