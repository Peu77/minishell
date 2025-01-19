/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:20:45 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 19:27:36 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <gcollector.h>

void	free_token(void *content)
{
	t_token	*token;

	token = content;
	gc_free_ptr(token->value);
	gc_free_ptr(token);
}

t_token	*create_token(t_token_type type, char *value, void *data)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->data = data;
	return (token);
}
