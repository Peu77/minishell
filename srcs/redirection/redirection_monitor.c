/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:17 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/16 20:11:14 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	save_file_descriptors(t_command **command)
{
	(*command)->saved_stdout = dup(STDOUT_FILENO);
	if ((*command)->saved_stdout == -1)
	{
		pev("dup failed for saving STDOUT");
		exit(EXIT_FAILURE);
	}
	(*command)->saved_stdin = dup(STDIN_FILENO);
	if ((*command)->saved_stdin == -1)
	{
		pev("dup failed for saving STDIN");
		exit(EXIT_FAILURE);
	}
}

void	redirection_monitor(t_command *command)
{
	t_list		*redirect_list;
	t_redirect	*redirect;

	save_file_descriptors(&command);
	redirect_list = command->redirect;
	while (redirect_list)
	{
		redirect = (t_redirect *)redirect_list->content;
		if (redirect->type == TOKEN_REDIRECT_OUTPUT)
			redirection_output(redirect);
		else if (redirect->type == TOKEN_REDIRECT_APPEND)
			redirection_append(redirect);
		else if (redirect->type == TOKEN_REDIRECT_INPUT)
			redirection_input(redirect);
		else if (redirect->type == TOKEN_REDIRECT_INPUT_APPEND)
			redirection_heredoc(redirect->file, command);
		else
		{
			pev("Unknown redirection type encountered");
			exit(EXIT_FAILURE);
		}
		redirect_list = redirect_list->next;
	}
}
