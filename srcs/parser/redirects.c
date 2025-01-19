/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:54:07 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 23:34:23 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <minishell.h>
#include <stdbool.h>

void	free_redirect(void *content)
{
	t_redirect	*redirect;

	redirect = content;
	gc_free_ptr(redirect->file);
	gc_free_ptr(redirect);
}

bool	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_INPUT || type == TOKEN_REDIRECT_OUTPUT
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_REDIRECT_INPUT_APPEND);
}

t_redirect	*create_redirect(int fd_left, int fd_right, t_token_type type,
		char *file)
{
	t_redirect	*redirect;

	redirect = gc_malloc(sizeof(t_redirect));
	redirect->fd_left = fd_left;
	redirect->fd_right = fd_right;
	redirect->type = type;
	redirect->file = file;
	return (redirect);
}

