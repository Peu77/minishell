/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:43:27 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 19:48:20 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gcollector.h>


void gc_list_clear(t_list **list, void (*del)(void *))
{
    t_list	*tmp;

    if (!list || !del)
        return ;
    while (*list)
    {
        tmp = *list;
        *list = (*list)->next;
        del(tmp->content);
        gc_free_ptr(tmp);
    }
}

