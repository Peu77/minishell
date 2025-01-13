/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:04:04 by eebert            #+#    #+#             */
/*   Updated: 2025/01/13 15:42:00 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>

static char* expand_env_vars(const char* input) {
    if (!input) return NULL;

    // First pass: calculate required size
    size_t size = 0;
    for (int i = 0; input[i]; i++) {
        if (input[i] == '$' && input[i + 1]) {
            char var_name[256] = {0};
            int j = 0;
            i++;

            while (input[i] && (ft_isalnum(input[i]) || input[i] == '_') && j < 255) {
                var_name[j++] = input[i++];
            }
            i--;

            const char* value = getenv(var_name);
            size += value ? strlen(value) : 0;
        } else {
            size++;
        }
    }

    char* result = (char*)malloc(size + 1);
    if (!result) return NULL;

    size_t pos = 0;
    for (int i = 0; input[i]; i++) {
        if (input[i] == '$' && input[i + 1]) {
            char var_name[256] = {0};
            int j = 0;
            i++;

            while (input[i] && (ft_isalnum(input[i]) || input[i] == '_') && j < 255) {
                var_name[j++] = input[i++];
            }
            i--;

            const char* value = getenv(var_name);
            if (value) {
                strcpy(result + pos, value);
                pos += strlen(value);
            }
        } else {
            result[pos++] = input[i];
        }
    }
    result[pos] = '\0';

    return result;
}

static bool is_match(const char *pattern, int pattern_len, const char *str) {
    if (pattern_len == 0) {
        return *str == '\0';
    }

    if (*pattern == '*') {
        if (is_match(pattern + 1, pattern_len - 1, str))
            return true;
        if (*str && is_match(pattern, pattern_len, str + 1))
            return true;
    }

    if (*str && *pattern == *str) {
        return is_match(pattern + 1, pattern_len - 1, str + 1);
    }

    return false;
}

int expand_wildcard(const char *old_pattern, int pattern_len, t_list **list, int* char_count) {
    int matches;

    char* pattern = expand_env_vars(old_pattern);

    printf("new pattern: %s\n", pattern);

    matches = 0;
    (void) matches;
    char *path = ".";
    DIR *dir = opendir(path);
    if (dir == NULL) {
        ft_putstr_fd("Error: Unable to open directory\n", 2);
        return 1;
    }

    char *file_name;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        file_name = entry->d_name;
        if(is_match(pattern, pattern_len, file_name)) {

            ft_lstadd_back(list, ft_lstnew(ft_strdup(file_name)));
            (*char_count) += ft_strlen(file_name);
            matches++;
        }
    }

    closedir(dir);
    free(pattern);

    return true;
}



static bool is_wildcard_separator(char c) {
    return (ft_isspace(c) || c == '\'' || c == '\"');
}

int get_wildcard_len(char *str) {
    int i;
    bool found_wildcard;

    i = 0;
    found_wildcard = false;
    while (str[i] && !is_wildcard_separator(str[i])) {
        if (str[i] == '*')
            found_wildcard = true;
        i++;
    }

    if (!found_wildcard)
        return 0;
    return i;
}


/*
int main() {
    char *str = "* $PATH";
    int len = get_wildcard_len(str);
    t_list *list = NULL;
    expand_wildcard(str, len, &list);
    ft_lstclear(&list, free);

    return 0;
}
*/

