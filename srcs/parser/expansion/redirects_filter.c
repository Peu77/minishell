/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_filter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:00:01 by eebert            #+#    #+#             */
/*   Updated: 2025/01/22 15:42:00 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>

static void	init_vars(int *exit_code, t_list **str_list, size_t *i)
{
	*exit_code = 0;
	*get_char_count() = 0;
	*str_list = NULL;
	*i = 0;
}

char	*filter_and_get_redirects(const char *input, t_list **redirects,
		int *exit_code)
{
	size_t			i;
	t_token_type	type;
	t_list			*str_list;
	const size_t	input_len = ft_strlen(input);

	init_vars(exit_code, &str_list, &i);
	while (i < input_len)
	{
		if (skip_safe_quotes(input, &i, &str_list))
			continue ;
		type = is_redirect(input, i);
		if (type == TOKEN_NONE || is_escaped(input, i))
			add_str_to_result(input, &i, &str_list, 1);
		else if (i < input_len)
		{
			if (!parse_redirect(redirects, input, type, &i))
			{
				*exit_code = 258;
				break ;
			}
		}
	}
	return (strlst_to_str(str_list));
}
