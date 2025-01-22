/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:56:08 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 15:27:09 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_escaped(const char *str, size_t i)
{
	size_t	backslashes;

	backslashes = 0;
	while (i > 0 && str[i - 1] == '\\')
	{
		backslashes++;
		i--;
	}
	return (backslashes % 2);
}

static void	handle_backslash(char *str, int *i, int *j, int len)
{
	if (str[*i] == '\\' && *i + 1 < len)
	{
		if (str[*i + 1] == '\\')
		{
			str[(*j)++] = '\\';
			str[(*j)++] = '\\';
			*i += 2;
		}
		else if (str[*i + 1] != '\\')
		{
			str[(*j)++] = str[*i + 1];
			*i += 2;
		}
	}
	else
		str[(*j)++] = str[(*i)++];
}

static void	process_quote_char(t_escape_data data)
{
	if (!*data.in_quotes)
	{
		*data.in_quotes = true;
		*data.quote_type = data.str[*data.i];
		data.str[(*data.j)++] = data.str[(*data.i)++];
	}
	else if (data.str[*data.i] == *data.quote_type)
	{
		*data.in_quotes = false;
		data.str[(*data.j)++] = data.str[(*data.i)++];
	}
	else
		data.str[(*data.j)++] = data.str[(*data.i)++];
}

static void	handle_quotes(t_escape_data data)
{
	if ((data.str[*data.i] == '"' || data.str[*data.i] == '\'') && (*data.i == 0
			|| data.str[*data.i - 1] != '\\'))
		process_quote_char(data);
	else
		handle_backslash(data.str, data.i, data.j, data.len);
}

char	*ft_unescape_string(char *str)
{
	int		i;
	int		j;
	int		len;
	char	quote_type;
	bool	in_quotes;

	if (!str)
		return (NULL);
	len = strlen(str);
	i = 0;
	j = 0;
	in_quotes = false;
	quote_type = 0;
	while (i < len)
		handle_quotes((t_escape_data){str, &i, &j, &in_quotes, &quote_type,
			len});
	str[j] = '\0';
	return (str);
}
