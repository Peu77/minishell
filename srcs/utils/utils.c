/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:37:15 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 20:08:33 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:00 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/16 11:21:59 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *src, size_t len)
{
	char	*dest;

	dest = (char *)gc_malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, len + 1);
	dest[len] = '\0';
	return (dest);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

char	*join_str_array(char **list, int size)
{
	char	*result;
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (i < size)
		len += ft_strlen(list[i++]) + 1;
	result = (char *)gc_add(ft_calloc(len + 1, sizeof(char)));
	if (!result)
		return (pev(ERROR_MALLOC), NULL);
	i = 0;
	while (i < size)
	{
		ft_strlcat(result, list[i], len + 1);
		if (i++ < size - 1)
			ft_strlcat(result, " ", len + 1);
	}
	return (result);
}
