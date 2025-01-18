/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:56:08 by eebert            #+#    #+#             */
/*   Updated: 2025/01/18 23:03:48 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_unescape_string(char *str)
{
    int	i;
    int	j;
    int	len;

    if (!str)
        return (NULL);
    len = strlen(str);
    i = 0;
    j = 0;
    while (i < len)
    {
        if (str[i] == '\\' && i + 1 < len)
            i++;
        else if ((str[i] == '"' || str[i] == '\'') &&
            (i == 0 || str[i - 1] != '\\'))
        {
            i++;
            continue ;
        }
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
    return (str);
}