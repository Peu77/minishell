/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:40:48 by eebert            #+#    #+#             */
/*   Updated: 2025/01/15 17:00:24 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <parse.h>

static size_t	get_env_var_len(const char *input, size_t max_len)
{
	int		i;
	size_t	len;
	char	var_name[MAX_VAR_LEN];
	int		j;

	i = -1;
	len = 0;
	while (input[++i] && i < (int)max_len)
	{
		if (input[i] == '$' && input[i + 1])
		{
			ft_bzero(var_name, MAX_VAR_LEN);
			j = 0;
			i++;
			while (input[i] && (ft_isalnum(input[i]) || input[i] == '_')
				&& j < MAX_VAR_LEN - 1)
				var_name[j++] = input[i++];
			i--;
			if (get_env_value(var_name, get_shell()->env))
				len += ft_strlen(get_env_value(var_name, get_shell()->env));
		}
		else
			len++;
	}
	return (len);
}

static void	insert_env_vars(const char *input, size_t len, char *result,
		size_t *pos)
{
	int		i;
	char	var_name[MAX_VAR_LEN];
	int		j;

	i = -1;
	while (input[++i] && i < (int)len)
	{
		if (input[i] == '$' && input[i + 1])
		{
			ft_bzero(var_name, MAX_VAR_LEN);
			j = 0;
			i++;
			while (input[i] && (ft_isalnum(input[i]) || input[i] == '_')
				&& j < MAX_VAR_LEN - 1)
				var_name[j++] = input[i++];
			i--;
			if (get_env_value(var_name, get_shell()->env))
			{
				strcpy(result + *pos, get_env_value(var_name, get_shell()->env));
				*pos += strlen(get_env_value(var_name, get_shell()->env));
			}
		}
		else
			result[(*pos)++] = input[i];
	}
}

char	*expand_env_vars(const char *input, size_t len)
{
	char	*result;
	size_t	pos;

	if (!input)
		return (NULL);
	result = malloc(get_env_var_len(input, len) + 1);
	if (!result)
		return (NULL);
	pos = 0;
	insert_env_vars(input, len, result, &pos);
	result[pos] = '\0';
	return (result);
}
