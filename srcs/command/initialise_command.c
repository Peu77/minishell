/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 12:59:20 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	get_redirection(t_command_test **command, t_list *redirection)
{
	(*command)->redirect = redirection;
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
		{
			printf(" ihave been here");
			free_command_split(arg);
			return (pe(ERROR_MALLOC));
		}
	}
	get_path(command);
	if (redirection)
		get_redirection(command, redirection);
	free_command_split(arg);

	return (1);
}
