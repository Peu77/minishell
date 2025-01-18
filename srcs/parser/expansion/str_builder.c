/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:02:57 by eebert            #+#    #+#             */
/*   Updated: 2025/01/18 21:51:43 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @return the amount of characters for the current string
 */
size_t	*get_char_count(void)
{
    static size_t	char_count = 0;

    return (&char_count);
}

/**
 * this function will convert a list of strings to a single string
 * based on the amount of get_char_count() characters
 * @param result_chars list of strings
 * @return new string
 */
char	*strlst_to_str(const t_list *result_chars)
{
    char	*result;
    int		cpy_offset;

    cpy_offset = 0;
    result = malloc(*get_char_count() + 1);
    if (!result)
        return (pe(ERROR_MALLOC), NULL);
    result[*get_char_count()] = '\0';
    while (result_chars)
    {
        ft_strlcpy(result + cpy_offset, result_chars->content, ft_strlen(result_chars->content)
            + 1);
        cpy_offset += ft_strlen(result_chars->content);
        result_chars = result_chars->next;
    }
    *get_char_count() = 0;
    return (result);
}

bool	add_char_to_result(const char *str, int *i, t_list **result_chars)
{
    char	*str_cpy;
    t_list	*new_node;

    str_cpy = ft_substr(str, *i, 1);
    if (!str_cpy)
        return (pe(ERROR_MALLOC), false);
    new_node = ft_lstnew(str_cpy);
    if (!new_node)
        return (free(str_cpy), pe(ERROR_MALLOC), false);
    (*get_char_count())++;
    (*i)++;
    return (ft_lstadd_back(result_chars, new_node), true);
}
