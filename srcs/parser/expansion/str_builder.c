/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:02:57 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 15:50:36 by eebert           ###   ########.fr       */
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
char	*strlst_to_str(t_list *result_chars)
{
    char	*result;
    int		cpy_offset;
    t_list*    tmp;

    tmp = result_chars;
    cpy_offset = 0;
    result = gc_malloc(*get_char_count() + 1);
    if (!result)
        return (gc_list_clear(&result_chars, gc_free_ptr), pe(ERROR_MALLOC), NULL);
    result[*get_char_count()] = '\0';
    while (result_chars)
    {
        ft_strlcpy(result + cpy_offset, result_chars->content, ft_strlen(result_chars->content)
            + 1);
        cpy_offset += ft_strlen(result_chars->content);
        result_chars = result_chars->next;
    }
    *get_char_count() = 0;
    gc_list_clear(&tmp, gc_free_ptr);
    return (result);
}

/**
 * this function will add a string to the list of strings
 * and increases the length of the str-builder
 * @param str the string from which the substring will be created
 * @param i the index from which the substring will start
 * @param result_chars  the list of strings
 * @param len the length of the substring
 * @return
 */
bool add_str_to_result(const char *str, size_t *i, t_list **result_chars, size_t len)
{
    char	*str_cpy;
    t_list	*new_node;

    str_cpy = ft_substr(str, *i, len);
    if (!str_cpy)
        return (pe(ERROR_MALLOC), false);
    new_node = ft_lstnew(str_cpy);
    if (!new_node)
        return (gc_free_ptr(str_cpy), pe(ERROR_MALLOC), false);
    (*get_char_count()) += len;
    (*i) += len;
    return (ft_lstadd_back(result_chars, new_node), true);
}
