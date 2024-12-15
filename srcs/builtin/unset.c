/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:11:49 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 20:37:44 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


extern char **environ;

void print_environ(void)
{
    char **envp = environ;

    while (*envp)
    {
        printf("%s\n", *envp);
        envp++;
    }
}

int	unset(t_command_test *command, t_env *env)
{
    char    **arg;
    int     result;
    int     unset_result;
    char    **envp;
    char    *var_to_remove;

    arg = ft_split(command->argument, ' ');
    result = 0;
    while (*arg)
    {
        // Remove from your internal env list
        unset_result = unset_variable(env, *arg);
        if (unset_result != 0)
            result = 1;
        
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
   print_environ() ;
    return (result);
}
