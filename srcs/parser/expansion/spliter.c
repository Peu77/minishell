/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:54:42 by eebert            #+#    #+#             */
/*   Updated: 2025/01/18 18:00:26 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdbool.h>

static bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static bool	matches_quote(char c, char quote_type)
{
	return (c == quote_type);
}

static size_t	count_words(char const *str)
{
	size_t	count;
	bool	in_word;
	bool	in_quotes;
	char	quote_type;

	count = 0;
	in_word = false;
	in_quotes = false;
	quote_type = 0;
	while (*str)
	{
		if (is_quote(*str) && !in_quotes)
		{
			in_quotes = true;
			quote_type = *str;
		}
		else if (matches_quote(*str, quote_type) && in_quotes)
		{
			in_quotes = false;
			quote_type = 0;
		}
		else if (!ft_isspace(*str) && !in_word)
		{
			in_word = true;
			count++;
		}
		else if (ft_isspace(*str) && in_word && !in_quotes)
			in_word = false;
		str++;
	}
	return (count);
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
		if (is_quote(str[len]) && !in_quotes)
		{
			in_quotes = true;
			quote_type = str[len];
		}
		else if (matches_quote(str[len], quote_type) && in_quotes)
		{
			in_quotes = false;
			quote_type = 0;
		}
		if (ft_isspace(str[len]) && !in_quotes)
			break ;
		len++;
	}
	return (len);
}

static char	*extract_word(char const *str, size_t len)
{
	char	*word;
	size_t	i;
	size_t	j;
	bool	in_quotes;
	char	quote_type;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = false;
	quote_type = 0;
	while (i < len)
	{
		if (is_quote(str[i]) && !in_quotes)
		{
			in_quotes = true;
			quote_type = str[i];
		}
		else if (matches_quote(str[i], quote_type) && in_quotes)
		{
			in_quotes = false;
			quote_type = 0;
		}
		else
			word[j++] = str[i];
		i++;
	}
	word[j] = '\0';
	return (word);
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
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (ft_isspace(*str))
			str++;
		word_len = get_word_length(str);
		result[i] = extract_word(str, word_len);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		str += word_len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

