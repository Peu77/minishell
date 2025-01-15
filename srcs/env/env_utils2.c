/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:42:14 by eebert            #+#    #+#             */
/*   Updated: 2025/01/15 17:00:36 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *key, char **env)
{
	int		key_len;

	key_len = ft_strlen(key);
	while (*env)
	{
		if (ft_strncmp(*env, key, key_len) == 0 && (*env)[key_len] == '=')
		{
			return (*env + key_len + 1);
		}
		env++;
	}
	return (NULL);
}
