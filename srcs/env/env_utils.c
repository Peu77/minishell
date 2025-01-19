/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:13:56 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 18:13:45 by eebert           ###   ########.fr       */
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

void	print_env_list(const bool filter_empty)
{
	t_list		*current;
	t_env_entry	*entry;

	current = get_shell()->env;
	while (current)
	{
		entry = current->content;
		if ((!entry->value || *entry->value == 0) && filter_empty) {
			current = current->next;
			continue;
		}
		ft_printf("%s", entry->key);
		if (entry->value && *entry->value)
			ft_printf("=%s", entry->value);
		ft_printf("\n");
		current = current->next;
	}
}

static void increase_shlvl(void)
{
	t_env_entry	*entry;
	char		*shlvl_str;
	int			shlvl;

	entry = get_env_entry("SHLVL");
	if (!entry)
	{
		add_env_pairstr("SHLVL=1");
		return ;
	}
	shlvl = ft_atoi(entry->value);
	if (shlvl == INT_MAX)
		return ;
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return ;
	free(entry->value);
	entry->value = shlvl_str;
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
	increase_shlvl();
	set_env_value("OLDPWD", "");
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
