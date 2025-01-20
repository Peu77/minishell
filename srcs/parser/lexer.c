/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:29 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 20:56:46 by eebert           ###   ########.fr       */
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
	if (*start_quote == input[pos] && !is_escaped(input, pos)  && *in_quote)
		*start_quote = 0;
	else if ((input[pos] == '\'' || input[pos] == '\"') && *start_quote == 0 && !is_escaped(input, pos))
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
		if (get_token_type(input, *i + string_i, *in_quote) != TOKEN_STRING)
			break ;
		string_i++;
	}
	if (start_quote == 0)
		*in_quote = false;
	if (string_i > 0)
	{
		if (!add_token(tokens, TOKEN_STRING, gc_add(ft_substr(input, *i, string_i))))
			return (false);
		*i += string_i;
	}
	return (true);
}

static bool	handle_token(const char *input, size_t *i, t_list **tokens,
		bool *in_quote)
{
	const t_token_type	type = get_token_type(input, *i, false);

	if (type != TOKEN_STRING)
	{
		if (!add_token(tokens, type, NULL) || type == TOKEN_END)
			return (false);
		*i += 1 + (type >= TOKEN_AND);
		return (true);
	}
	return (lex_string_token(input, i, tokens, in_quote));
}

bool check_parentheses_count(t_list** tokens) {
	int open;
	int close;
	t_list* tmp;

	tmp = *tokens;

	open = 0;
	close = 0;
	while (tmp) {
		if (((t_token*)(tmp)->content)->type == TOKEN_PARENTHESES_OPEN)
			open++;
		if (((t_token*)(tmp)->content)->type == TOKEN_PARENTHESES_CLOSE)
			close++;
		tmp = tmp->next;
	}

	return open == close;
}

int get_redirect_parse_error(t_list* tokens) {
	int exit_code;
	t_list* redirects;
	char* tmp;

	while (tokens) {
		if(((t_token*)(tokens)->content)->type == TOKEN_STRING) {
			redirects = NULL;
			tmp = filter_and_get_redirects(((t_token*)(tokens)->content)->value, &redirects, &exit_code);
			gc_list_clear(&redirects, free_redirect);
			gc_free_ptr(tmp);

			if(exit_code != 0)
				return exit_code;
		}
		tokens = tokens->next;
	}
	return 0;
}

bool	lex_tokens(const char *input, t_list **tokens)
{
	const size_t	len = ft_strlen(input);
	size_t			i;
	bool			in_quote;
	int redirect_parse_error;

	in_quote = false;
	i = 0;
	while (i < len)
	{
		if (!handle_token(input, &i, tokens, &in_quote))
			break;
	}
	if (i != len || in_quote)
	{
		if (in_quote)
			pe("parse error near '\\n'");
		return (gc_list_clear(tokens, free_token), false);
	}
	if(!check_parentheses_count(tokens)) {
		get_shell()->exit_status = 2;
		return (pe("parse error, the parentheses don't match"), gc_list_clear(tokens, free_token), false);
	}

	redirect_parse_error = get_redirect_parse_error(*tokens);
	if(redirect_parse_error != 0) {
		get_shell()->exit_status = redirect_parse_error;
		return (pe("parse error, each redirect should have an filename"), gc_list_clear(tokens, free_token), false);
	}

	return (true);
}
