/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:03 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/13 19:50:01 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_list(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

char	**initialise_env(char **env)
{
	static char	**environ = NULL;

	if (env)
		environ = env;
	return (environ);
}

static char	*initialize_stock(char *str, char **stock, int *i)
{
	if (str != NULL)
	{
		if (*stock)
			free(*stock);
		*stock = ft_strdup(str);
		*i = 0;
		if (!*stock)
			return (NULL);
	}
	return (*stock);
}

char	*ft_strtok(char *str, const char delim)
{
	static char	*stock = NULL;
	static int	i = 0;
	char		*ptr;
	int			flg;

	if (initialize_stock(str, &stock, &i) == NULL)
		return (NULL);
	flg = 0;
	ptr = NULL;
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
			i++;
			break ;
		}
		i++;
	}
	return (ptr);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
