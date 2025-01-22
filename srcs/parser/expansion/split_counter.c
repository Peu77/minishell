/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:09:35 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 15:11:59 by eebert           ###   ########.fr       */
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

static void	count_word_helper(const char *str, size_t *i, bool *in_quotes,
		char *quote_type)
{
	while (str[*i])
	{
		if (is_quote(str[*i]) && !*in_quotes && !is_escaped(str, *i))
		{
			*in_quotes = true;
			*quote_type = str[*i];
		}
		else if (matches_quote(str[*i], *quote_type) && *in_quotes
			&& !is_escaped(str, *i))
		{
			*in_quotes = false;
			*quote_type = 0;
			(*i)++;
			if (!str[*i] || (ft_isspace(str[*i]) && !*in_quotes))
				break ;
			continue ;
		}
		if (ft_isspace(str[*i]) && !*in_quotes && !is_escaped(str, *i))
			break ;
		(*i)++;
	}
}

size_t	count_words(char const *str)
{
	size_t	count;
	bool	in_quotes;
	char	quote_type;
	size_t	i;

	count = 0;
	in_quotes = false;
	quote_type = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]) && !in_quotes)
			(i)++;
		if (!str[i])
			break ;
		(count)++;
		count_word_helper(str, &i, &in_quotes, &quote_type);
	}
	return (count);
}
