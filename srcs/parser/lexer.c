/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:29 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 17:13:26 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <minishell.h>
#include <stdbool.h>

static void	quote_logic(char *start_quote, bool *in_quote, const char *input,
		int pos)
{
	if (*start_quote == 0)
		*in_quote = false;
	if (*start_quote == input[pos] && *in_quote)
		*start_quote = 0;
	else if ((input[pos] == '\'' || input[pos] == '\"') && *start_quote == 0)
	{
		*in_quote = true;
		*start_quote = input[pos];
	}
}

static bool	lex_string_token(const char *input, size_t *i, t_list **tokens,
		bool *in_quote)
{
	int		string_i;
	char	start_quote;

	string_i = 0;
	start_quote = 0;
	*in_quote = false;
	while (input[*i + string_i])
	{
		quote_logic(&start_quote, in_quote, input, (int)*i + string_i);
		if (get_token_type(input + *i + string_i, *in_quote) != TOKEN_STRING)
			break ;
		string_i++;
	}
	if (start_quote == 0)
		*in_quote = false;
	if (string_i > 0)
	{
		if (!add_token(tokens, TOKEN_STRING, ft_substr(input, *i, string_i)))
			return (false);
		*i += string_i;
	}
	return (true);
}

static bool	handle_token(const char *input, size_t *i, t_list **tokens,
		bool *in_quote)
{
	const t_token_type	type = get_token_type(input + *i, false);

	if (is_redirect_token(type))
	{
		if (!parse_redirect_to_token(tokens, input, type, i))
			return (false);
		return (true);
	}
	if (type != TOKEN_STRING)
	{
		if (!add_token(tokens, type, NULL) || type == TOKEN_END)
			return (false);
		*i += 1 + (type >= TOKEN_AND);
		return (true);
	}
	return (lex_string_token(input, i, tokens, in_quote));
}

bool	lex_tokens(char *input, t_list **tokens)
{
	const size_t	len = ft_strlen(input);
	size_t			i;
	bool			in_quote;

	in_quote = false;
	i = 0;
	while (i < len)
	{
		if (!handle_token(input, &i, tokens, &in_quote))
			break ;
	}
	if (i != len || in_quote)
	{
		if (in_quote)
			pe("parse error near `\\n'");
		return (ft_lstclear(tokens, free_token), false);
	}
	return (true);
}
