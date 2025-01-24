/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:53:37 by eebert            #+#    #+#             */
/*   Updated: 2025/01/21 17:27:49 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void	print_command(t_command *command)
{
	printf("\n STRUCT COMMAND : \n ");
	if (!command)
	{
		printf("Command is NULL.\n");
		return ;
	}
	printf("Command Name: %s\n",
		command->command_name ? command->command_name : "(NULL)");
	printf("Arguments: %s\n", command->argument ? command->argument : "(NULL)");
	printf("Paths: %s\n", command->path ? command->path : "(NULL)");
}
*/

t_redirect	*copy_redirect_node(t_redirect *original)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)gc_malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->fd_left = original->fd_left;
	new_redirect->fd_right = original->fd_right;
	new_redirect->type = original->type;
	if (original->file)
	{
		new_redirect->file = gc_add(ft_strdup(original->file));
		if (!new_redirect->file)
		{
			gc_free_ptr(new_redirect);
			return (NULL);
		}
	}
	else
		new_redirect->file = NULL;
	return (new_redirect);
}

static void	put_redirection(t_list *redirection, t_command **command)
{
	(*command)->redirect = redirection;
	(*command)->saved_stdout = 0;
}

int	transform_node_to_command(char **argv, t_command **command,
		t_list *redirection, char *heredoc_filename)
{
	*command = gc_malloc(sizeof(t_command));
	ft_memset(*command, 0, sizeof(t_command));
	if (!argv[0] && ft_lstsize(redirection) > 0)
		argv[0] = gc_add(ft_strdup("cat"));
	if (!argv[0])
		return (free_string_array(argv), false);
	(*command)->command_name = gc_add(ft_strdup(argv[0]));
	(*command)->heredoc_filename = heredoc_filename;
	if (!(*command)->command_name)
		return (pe(ERROR_MALLOC));
	(*command)->argv = argv;
	get_path(command);
	if (redirection)
		put_redirection(redirection, command);
	return (1);
}
