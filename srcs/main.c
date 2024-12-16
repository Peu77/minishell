/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:26 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/16 20:23:05 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_status = 0;

int	main(int argc, char **argv)
{
	if (argc >= 2)
	{
		if (argc == 2)
			minishell_non_interactive_argument(argv[1]);
		else
			return (pec(ERROR_SET_ARGUMENT));
	}
	else if (isatty(STDIN_FILENO))
		minishell_interactive();
	else
		minishell_non_interactive();
	return (EXIT_SUCCESS);
}
