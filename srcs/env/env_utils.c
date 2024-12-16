/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:10:03 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 07:02:10 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_env_list()
{
    char **envp = environ;

    while (*envp)
    {
        printf("%s\n", *envp);
        envp++;
    }
}
