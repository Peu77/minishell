/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:22:12 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 21:34:19 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:17 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/17 13:49:13 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	save_file_descriptors(t_command **command)
{
	(*command)->saved_stdout = dup(STDOUT_FILENO);
	gc_add_fd((*command)->saved_stdout);
	if ((*command)->saved_stdout == -1)
	{
		pev("dup failed for saving STDOUT");
		destroy_minishell(EXIT_FAILURE);
	}
	(*command)->saved_stdin = dup(STDIN_FILENO);
	gc_add_fd((*command)->saved_stdin);
	if ((*command)->saved_stdin == -1)
	{
		pev("dup failed for saving STDIN");
		destroy_minishell(EXIT_FAILURE);
	}
}

bool	redirection_monitor(t_command *command)
{
	t_list		*redirect_list;
	t_redirect	*redirect;

	save_file_descriptors(&command);
	redirect_list = command->redirect;
	while (redirect_list)
	{
		redirect = (t_redirect *)redirect_list->content;
		if (redirect->type == TOKEN_REDIRECT_OUTPUT)
		{
			if (!redirection_output(redirect))
				return (false);
		}
		else if (redirect->type == TOKEN_REDIRECT_APPEND)
		{
			if (!redirection_append(redirect))
				return (false);
		}
		else if (redirect->type == TOKEN_REDIRECT_INPUT)
		{
			if (!redirection_input(redirect))
				return (false);
		}
		else if (redirect->type == TOKEN_REDIRECT_INPUT_APPEND)
		{
			if (redirection_heredoc(redirect->file) != 0)
				return (false);
		}
		else
		{
			pev("Unknown redirection type encountered");
			destroy_minishell(EXIT_FAILURE);
		}
		redirect_list = redirect_list->next;
	}
	return (true);
}
