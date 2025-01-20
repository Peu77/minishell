/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:25:26 by eebert            #+#    #+#             */
/*   Updated: 2025/01/20 14:34:15 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list** get_gc_head_files(void)
{
    static t_list *gc_head = NULL;

    return (&gc_head);
}

void gc_close_fds() {
    t_list* current = *get_gc_head_files();
    t_list* next;

    while (current) {
        next = current->next;
        close(*((int*)current->content));
        free(current->content);
        free(current);
        current = next;
    }
}

int gc_add_fd(int fd)
{
    t_list *new_node;

    int* fd_ptr = malloc(sizeof(int));
    if(!fd_ptr)
        destroy_minishell(EXIT_FAILURE);
    *fd_ptr = fd;
    new_node = ft_lstnew(fd_ptr);
    if (!new_node)
         destroy_minishell(EXIT_FAILURE);
    ft_lstadd_back(get_gc_head_files(), new_node);
    return (fd);
}

void gc_close_fd(int fd) {
    t_list *current;
    t_list *previous;

    current = *get_gc_head_files();
    previous = NULL;
    while (current)
    {
        if (*((int*)current->content) == fd)
        {
            if (previous)
                previous->next = current->next;
            else
                *get_gc_head_files() = current->next;
            close(fd);
            free(current->content);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
    close(fd);
}