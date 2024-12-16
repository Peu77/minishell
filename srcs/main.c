/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:26 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 17:50:52 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int g_last_exit_status = 0;

int main(int argc, char **argv)
{

    pe("WELCOME TO MINISHELL");
    if (argc >= 2)
    {
		if(argc == 2)
		{
        	printf("Non-interactive mode with argument: %s\n", argv[1]);
   			minishell_non_interactive_argument(argv[1]);
		}
		else
			return pec(ERROR_SET_ARGUMENT);
    }
    else if (isatty(STDIN_FILENO))
    {
        printf("Interactive mode\n");
        minishell_interactive();
    }
    else
    {
        printf("Non-interactive mode\n");
        minishell_non_interactive();
    }
    return (EXIT_SUCCESS);
}
