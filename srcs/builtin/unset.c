/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:49 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 18:11:50 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void print_environ(void)
{
    char **envp = environ;

    while (*envp)
    {
        printf("%s\n", *envp);
        envp++;
    }
}

int	ft_unset(t_command_test *command)
{
    char    **arg;
    int     result;
    char    **envp;
    char    *var_to_remove;

    arg = ft_split(command->argument, ' ');
    result = 0;
    while (*arg)
    {
        var_to_remove = *arg;
        envp = environ;
        while (*envp)
        {
            if (strncmp(*envp, var_to_remove, strlen(var_to_remove)) == 0 && (*envp)[strlen(var_to_remove)] == '=')
            {
                while (*envp)
                {
                    *envp = *(envp + 1);
                    envp++;
                }
                break;
            }
            envp++;
        }
        arg++;
    }
    return (result);
}
