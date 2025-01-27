/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:38:30 by eebert            #+#    #+#             */
/*   Updated: 2025/01/25 17:02:40 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_empty_str_token(t_token *token)
{
	if (token->type != TOKEN_STRING)
		return (false);
	return (is_empty_str(token->value));
}

bool	is_empty_str(const char *str)
{
	int	i;

	if (str == NULL || ft_strlen(str) == 0)
		return (true);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}
