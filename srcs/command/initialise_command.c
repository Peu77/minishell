/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:39:38 by eebert            #+#    #+#             */
/*   Updated: 2025/01/13 19:18:13 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/18 17:01:02 by ftapponn         ###   ########.fr       */
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

int	concatenate_arguments(char **arg, char **result)
{
	int		i;
	size_t	total_length;

	i = 0;
	total_length = 0;
	while (arg[++i])
		total_length += ft_strlen(arg[i]) + 1;
	*result = malloc(total_length);
	if (!(*result))
		return (pe(ERROR_MALLOC));
	(*result)[0] = '\0';
	i = 0;
	while (arg[++i])
	{
		ft_strlcat(*result, arg[i], total_length);
		if (arg[i + 1])
			ft_strlcat(*result, " ", total_length);
	}
	return (1);
}

t_redirect	*copy_redirect_node(t_redirect *original)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->fd_left = original->fd_left;
	new_redirect->fd_right = original->fd_right;
	new_redirect->type = original->type;
	if (original->file)
	{
		new_redirect->file = ft_strdup(original->file);
		if (!new_redirect->file)
		{
			free(new_redirect);
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

int	transform_node_to_command(char *value, t_command **command,
		t_list *redirection)
{
	char	**arg;

	*command = malloc(sizeof(t_command));
	if (!(*command))
		return (pe(ERROR_MALLOC));
	ft_memset(*command, 0, sizeof(t_command));
	if (!(*command))
		return (pe(ERROR_MALLOC));
	arg = ft_split(value, ' ');
	if (!arg)
		return (pe(ERROR_SPLIT));
	(*command)->command_name = ft_strdup(arg[0]);
	if (!arg[1])
		(*command)->argument = NULL;
	else
	{
		if (concatenate_arguments(arg, &((*command)->argument)) != 1)
			return (free_command_split(arg), pe(ERROR_MALLOC));
	}
	get_path(command);
	if (redirection)
		put_redirection(redirection, command);
	free_command_split(arg);
	return (1);
}
