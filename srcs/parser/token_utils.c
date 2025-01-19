/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:20:45 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 17:19:18 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}

t_token	*create_token(t_token_type type, char *value, void *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->data = data;
	return (token);
}
