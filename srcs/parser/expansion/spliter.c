/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:54:42 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 15:40:21 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <parse.h>
#include <stdbool.h>

static bool is_quote(char c)
{
    return (c == '"' || c == '\'');
}

static bool matches_quote(char c, char quote_type)
{
    return (c == quote_type);
}

static size_t count_words(char const *str)
{
    size_t count;
    bool   in_quotes;
    char   quote_type;
    int    i;

    count = 0;
    in_quotes = false;
    quote_type = 0;
    i = 0;
    while (str[i])
    {
        while (str[i] && ft_isspace(str[i]) && !in_quotes)
            i++;
        if (!str[i])
            break;

        count++;

        while (str[i])
        {
            if (is_quote(str[i]) && !in_quotes && !is_escaped(str, i))
            {
                in_quotes = true;
                quote_type = str[i];
            }
            else if (matches_quote(str[i], quote_type) && in_quotes && !is_escaped(str, i))
            {
                in_quotes = false;
                quote_type = 0;
                i++;
                if (!str[i] || (ft_isspace(str[i]) && !in_quotes))
                    break;
                continue;
            }
            if (ft_isspace(str[i]) && !in_quotes && !is_escaped(str, i))
                break;
            i++;
        }
    }
    return (count);
}

static size_t get_word_length(char const *str)
{
    size_t len;
    bool   in_quotes;
    char   quote_type;

    len = 0;
    in_quotes = false;
    quote_type = 0;
    while (str[len])
    {
        if (is_quote(str[len]) && !in_quotes && !is_escaped(str, len))
        {
            in_quotes = true;
            quote_type = str[len];
        }
        else if (matches_quote(str[len], quote_type) && in_quotes && !is_escaped(str, len))
        {
            len++;
            in_quotes = false;
            quote_type = 0;
            if (!str[len] || (ft_isspace(str[len]) && !in_quotes))
                break;
            continue;
        }
        if (ft_isspace(str[len]) && !in_quotes && !is_escaped(str, len))
            break;
        len++;
    }
    return (len);
}

static char *extract_word(char const *str, size_t len)
{
    char   *word;
    size_t i;
    size_t j;
    bool   in_quotes;
    char   quote_type;

    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    i = 0;
    j = 0;
    in_quotes = false;
    quote_type = 0;
    while (i < len)
    {
        if (is_quote(str[i]) && !in_quotes && !is_escaped(str, i))
        {
            quote_type = str[i];
            in_quotes = true;
        }
        else if (matches_quote(str[i], quote_type) && in_quotes && !is_escaped(str, i))
        {
            quote_type = 0;
            in_quotes = false;
        }
        else if (str[i] == '\\' && i + 1 < len &&
                (is_quote(str[i + 1]) || ft_isspace(str[i + 1]) || str[i + 1] == '\\'))
        {
            i++;
            word[j++] = str[i];
        }
        else
            word[j++] = str[i];
        i++;
    }
    word[j] = '\0';
    return (word);
}

char **split_quotes(char const *str)
{
    char   **result;
    size_t word_count;
    size_t i;
    size_t word_len;

    if (!str)
        return (NULL);
    word_count = count_words(str);
    result = malloc(sizeof(char *) * (word_count + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (i < word_count)
    {
        while (ft_isspace(*str))
            str++;
        word_len = get_word_length(str);
        result[i] = extract_word(str, word_len);
        if (!result[i])
        {
            while (i > 0)
                free(result[--i]);
            free(result);
            return (NULL);
        }
        str += word_len;
        i++;
    }
    result[i] = NULL;
    return (result);
}