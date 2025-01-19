/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:56:08 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 13:20:44 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool is_escaped(const char *str, size_t i)
{
    size_t backslashes;

    backslashes = 0;
    while (i > 0 && str[i - 1] == '\\')
    {
        backslashes++;
        i--;
    }
    return (backslashes % 2);
}

char *ft_unescape_string(char *str)
{
    int i;
    int j;
    int len;
    char quote_type;
    bool in_quotes;

    if (!str)
        return (NULL);
    len = strlen(str);
    i = 0;
    j = 0;
    in_quotes = false;
    quote_type = 0;
    while (i < len)
    {
        if (str[i] == '\\' && i + 1 < len)
        {
            if (str[i + 1] == '\\')
            {
                str[j++] = '\\';
                i += 2;
            }
            else
            {
                str[j++] = str[i + 1];
                i += 2;
            }
        }
        else if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
        {
            if (!in_quotes)
            {
                in_quotes = true;
                quote_type = str[i];
                str[j++] = str[i++];
            }
            else if (str[i] == quote_type)
            {
                in_quotes = false;
                str[j++] = str[i++];
            }
            else
                str[j++] = str[i++];
        }
        else
            str[j++] = str[i++];
    }
    str[j] = '\0';
    return (str);
}