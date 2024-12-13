/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:08:00 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/13 22:02:12 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_newline(char *buffer) 
{
    size_t len = ft_strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

char *ft_strndup(const char *src, size_t len)
{
    char *dest = (char *)malloc(len + 1);
    if (!dest)
        return NULL;
    ft_strlcpy(dest, src, len + 1);
    dest[len] = '\0';
    return dest;
}

long ft_atol(const char *str)
{
    long result = 0;
    int sign = 1;

    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\v' || *str == '\f')
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

