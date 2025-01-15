/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:42:14 by eebert            #+#    #+#             */
/*   Updated: 2025/01/15 16:44:03 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *key, char **env)
{
	int		key_len;
	char	*value;

	key_len = ft_strlen(key);
	while (*env)
	{
		if (ft_strncmp(*env, key, key_len) == 0 && (*env)[key_len] == '=')
		{
			value = ft_strdup(*env + key_len + 1);
			if (!value)
				return (NULL);
			return (value);
		}
		env++;
	}
	return (NULL);
}
