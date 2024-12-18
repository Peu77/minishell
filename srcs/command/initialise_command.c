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
void	print_command(t_command_test *command)
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

t_list	*copy_redirection_list(t_list *redirection)
{
	t_list		*new_list;
	t_list		*current;
	t_list		*new_node;
	t_redirect	*new_redirect;

	new_list = NULL;
	current = redirection;
	while (current)
	{
		new_redirect = copy_redirect_node((t_redirect *)(current->content));
		if (!new_redirect)
			return (NULL);
		new_node = ft_lstnew(new_redirect);
		if (!new_node)
		{
			free(new_redirect->file);
			free(new_redirect);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

int	get_redirection(t_command_test **command, t_list *redirection)
{
	(*command)->redirect = copy_redirection_list(redirection);
	(*command)->saved_stdout = 0;
	return (1);
}

int	transform_node_to_command(char *value, t_command_test **command,
		t_list *redirection)
{
	char	**arg;

	*command = malloc(sizeof(t_command_test));
	if (!(*command))
		return (pe(ERROR_MALLOC));
	ft_memset(*command, 0, sizeof(t_command_test));
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
		get_redirection(command, redirection);
	free_command_split(arg);
	return (1);
}
