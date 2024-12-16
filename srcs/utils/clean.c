/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:46 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 20:14:53 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	free_command_split(char **command_split)
{
	int	i;

	i = -1;
	if (!command_split)
		return ;
	while (command_split[++i])
		free(command_split[i]);
	free(command_split);
}

static void	del_redirect(void *content)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)content;
	if (redirect->file)
		free(redirect->file);
	free(redirect);
}

void	free_command(t_command_test **command)
{
	if (!command || !*command)
		return ;
	if ((*command)->path)
	{
		free((*command)->path);
		(*command)->path = NULL;
	}
	if ((*command)->command_name)
	{
		free((*command)->command_name);
		(*command)->command_name = NULL;
	}
	if ((*command)->argument)
	{
		free((*command)->argument);
		(*command)->argument = NULL;
	}
	if ((*command)->redirect)
	{
		ft_lstclear(&(*command)->redirect, del_redirect);
		(*command)->redirect = NULL;
	}
	if ((*command)->saved_stdout > 0)
	{
		close((*command)->saved_stdout);
		(*command)->saved_stdout = 0;
	}
	if ((*command)->saved_stdin > 0)
	{
		close((*command)->saved_stdin);
		(*command)->saved_stdin = 0;
	}
	free(*command);
	*command = NULL;
}
