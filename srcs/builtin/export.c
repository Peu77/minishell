/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:31 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 18:44:14 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strtok(char *str, const char delim)
{
	static char	*stock = NULL;
	static int	i = 0;
	char		*ptr;
	int			flg;

	flg = 0;
	ptr = NULL;
	if (str != NULL)
	{
		stock = ft_strdup(str);
		i = 0;
	}
	while (stock[i] != '\0')
	{
		if (flg == 0 && stock[i] != delim)
		{
			flg = 1;
			ptr = &stock[i];
		}
		else if (flg == 1 && stock[i] == delim)
		{
			stock[i] = '\0';
			i += 1;
			break ;
		}
		i += 1;
	}
	return (ptr);
}

t_env	*create_env_node(char *variable_name, char *variable_value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->variable_name = ft_strdup(variable_name);
	new_node->variable_value = ft_strdup(variable_value);
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

void	add_to_env(t_env *env, char *variable_name, char *variable_value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->variable_name, variable_name,
				ft_strlen(variable_name)) == 0)
			return ;
		temp = temp->next;
	}
	new_node = create_env_node(variable_name, variable_value);
	if (!new_node)
		return ;
	if (env == NULL)
		env = new_node;
	else
	{
		temp = env;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->previous = temp;
	}
}

int	export_command(t_command_test *command, t_env *env)
{
	char	*arg_copy;
	char	*token;
	char	*equals_pos;
	char	*variable_name;
	char	*variable_value;

	if (!command || !command->argument)
		return (1);
	arg_copy = ft_strdup(command->argument);
	token = ft_strtok(arg_copy, ' ');
	while (token)
	{
		equals_pos = ft_strchr(token, '=');
		if (equals_pos)
		{
			*equals_pos = '\0';
			variable_name = token;
			variable_value = equals_pos + 1;
			add_to_env(env, variable_name, variable_value);
		}
		token = ft_strtok(NULL, ' ');
	}
	free(arg_copy);
	return (0);
}
