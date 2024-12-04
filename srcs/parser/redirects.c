/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:54:07 by eebert            #+#    #+#             */
/*   Updated: 2024/12/04 11:14:00 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>
#include <stdbool.h>

void free_redirect(t_redirect *redirect) {
    free(redirect->file);
    free(redirect);
}

bool is_redirect_token(t_token *token) {
    return token->type == TOKEN_REDIRECT_INPUT || token->type == TOKEN_REDIRECT_OUTPUT ||
           token->type == TOKEN_REDIRECT_APPEND;
}

/**
 * parse all redirects and save them in the redirects list also skip all the command tokens and return the last token
 * @param redirects
 * @param tokens
 * @return the last token of the redirect/commands section
 */
t_list *parse_redirects(t_list **redirects, t_list *tokens) {
    t_list* new_node;

    while (tokens && (is_redirect_token(tokens->content) ||
                      ((t_token *) tokens->content)->type == TOKEN_STRING)) {
        t_token *token = tokens->content;

        if (token->type != TOKEN_STRING) {
            printf("creating redirect\n");
            t_redirect *old_redirect = token->data;
            t_redirect *redirect = malloc(sizeof(t_redirect));
            if(!redirect)
                return NULL;
            printf("fd_left: %d, fd_right: %d, file: %s\n", old_redirect->fd_left, old_redirect->fd_right,
                   old_redirect->file);
            redirect->fd_left = old_redirect->fd_left;
            redirect->fd_right = old_redirect->fd_right;
            redirect->file = ft_strdup(old_redirect->file);
            if(!redirect->file && old_redirect->file)
                return (free(redirect), NULL);
            new_node = ft_lstnew(redirect);
            if(!new_node)
                return (free_redirect(redirect), NULL);
            ft_lstadd_back(redirects, new_node);
        }
        tokens = tokens->next;
    }

    return tokens;
}
