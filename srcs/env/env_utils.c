/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:13:56 by eebert            #+#    #+#             */
/*   Updated: 2025/01/17 16:14:48 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:03 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/14 18:46:15 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <minishell.h>

void	print_env_list(void)
{
	t_list		*current;
	t_env_entry	*entry;

	current = get_shell()->env;
	while (current)
	{
		entry = current->content;
		printf("%s=%s\n", entry->key, entry->value);
		current = current->next;
	}
}

bool	initialise_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!add_env_pairstr(env[i]))
			return (false);
		i++;
	}
	return (true);
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
