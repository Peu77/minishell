/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:02:36 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 15:12:55 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static bool	matches_quote(char c, char quote_type)
{
	return (c == quote_type);
}

static void	handle_word_char(const char *str, size_t len, char *word,
		t_split_extractor split_extractor)
{
	if (is_quote(str[*split_extractor.i]) && !*split_extractor.in_quotes
		&& !is_escaped(str, *split_extractor.i))
	{
		*split_extractor.quote_type = str[*split_extractor.i];
		*split_extractor.in_quotes = true;
	}
	else if (matches_quote(str[*split_extractor.i], *split_extractor.quote_type)
		&& *split_extractor.in_quotes && !is_escaped(str, *split_extractor.i))
	{
		*split_extractor.quote_type = 0;
		*split_extractor.in_quotes = false;
	}
	else if (str[*split_extractor.i] == '\\' && *split_extractor.i + 1 < len
		&& (is_quote(str[*split_extractor.i + 1])
			|| ft_isspace(str[*split_extractor.i + 1]) || str[*split_extractor.i
				+ 1] == '\\'))
	{
		(*split_extractor.i)++;
		word[(*split_extractor.j)++] = str[*split_extractor.i];
	}
	else
		word[(*split_extractor.j)++] = str[*split_extractor.i];
}

char	*extract_word(char const *str, size_t len)
{
	char	*word;
	size_t	i;
	size_t	j;
	bool	in_quotes;
	char	quote_type;

	word = gc_add(ft_calloc((len + 1), (sizeof(char))));
	i = -1;
	j = 0;
	in_quotes = false;
	quote_type = 0;
	while (++i < len)
		handle_word_char(str, len, word, (t_split_extractor){&i, &j, &in_quotes,
			&quote_type});
	return (word);
}
