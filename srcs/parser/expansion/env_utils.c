/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:40:48 by eebert            #+#    #+#             */
/*   Updated: 2025/01/14 12:06:14 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parse.h>

static size_t	get_env_var_len(const char *input)
{
	int		i;
	size_t	len;
	char	var_name[MAX_VAR_LEN];
	int		j;

	i = -1;
	len = 0;
	while (input[++i])
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
			if (getenv(var_name))
				len += ft_strlen(getenv(var_name));
		}
		else
			len++;
	}
	return (len);
}

static void	insert_env_vars(const char *input, char *result, size_t *pos)
{
	int		i;
	char	var_name[MAX_VAR_LEN];
	int		j;

	i = -1;
	while (input[++i])
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
			if (getenv(var_name))
			{
				strcpy(result + *pos, getenv(var_name));
				*pos += strlen(getenv(var_name));
			}
		}
		else
			result[(*pos)++] = input[i];
	}
}

char	*expand_env_vars(const char *input)
{
	char	*result;
	size_t	pos;

	if (!input)
		return (NULL);
	result = malloc(get_env_var_len(input) + 1);
	if (!result)
		return (NULL);
	pos = 0;
	insert_env_vars(input, result, &pos);
	result[pos] = '\0';
	return (result);
}
