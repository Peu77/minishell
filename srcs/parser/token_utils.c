/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:20:45 by eebert            #+#    #+#             */
/*   Updated: 2024/12/04 16:22:32 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void free_token(void *content) {
    t_token *token;

    token = content;
    free(token->value);
    if(is_redirect_token(token->type) && token->data)
        free_redirect(token->data);
    free(token);
}