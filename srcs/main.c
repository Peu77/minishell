/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:26 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/11 17:39:41 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	if (env)
		initialise_env(env);
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
