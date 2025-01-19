/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:32:53 by eebert            #+#    #+#             */
/*   Updated: 2025/01/19 21:15:01 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list** get_gc_head(void)
{
    static t_list *gc_head = NULL;

    return (&gc_head);
}

void gc_free(void)
{
    ft_lstclear(get_gc_head(), free);
    *get_gc_head() = NULL;
}

void *gc_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        destroy_minishell(EXIT_FAILURE);
    return (gc_add(ptr));
}

void *gc_add(void *ptr)
{
    t_list *new_node;

    if(!ptr)
        destroy_minishell(EXIT_FAILURE);
    new_node = ft_lstnew(ptr);
    if (!new_node)
        destroy_minishell(EXIT_FAILURE);
    ft_lstadd_back(get_gc_head(), new_node);
    return (ptr);
}

void gc_free_ptr(void* addr)
{
    t_list *current;
    t_list *previous;

    current = *get_gc_head();
    previous = NULL;
    while (current)
    {
        if (current->content == addr)
        {
            if (previous)
                previous->next = current->next;
            else
                *get_gc_head() = current->next;
            free(current->content);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
    free(addr);
}