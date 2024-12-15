/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:07:33 by ftapponn          #+#    #+#             */
/*   Updated: 2024/12/15 20:26:45 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void minishell_interactive(t_env *env)
{
    char *user_prompt;
	t_command_test *command;
	t_ast_node *node;

	user_prompt = NULL;
	command = NULL;
    //main_signals();
    while (1)
    {
        if (!get_user_prompt(&user_prompt, env))
            break;
 		node = parse(user_prompt);
		if (node == NULL)
        {
            free(user_prompt);
            continue;
        }
        if (node == PARSE_ERROR)
        {
            free(user_prompt);
            pec("parse error\n");
            continue;
        }
        print_ast_node(node, 0);
        tree_monitor(node, command, env);
        free_ast_node(node);
		free_command(&command);
        free(user_prompt);
    }
}

void minishell_non_interactive(t_env *env)
{
    char *line = NULL;
 	t_command_test *command;
	t_ast_node *node;

    while ((line = readline(NULL)) != NULL)
    {
        if (*line == '\0')
        {
            free(line);
            continue;
        }
        command = NULL;
        node = parse(line);
        if (node == NULL || node == PARSE_ERROR)
        {
            pec("parse error\n");
            free(line);
            continue;
        }
        tree_monitor(node, command, env);
        free_ast_node(node);
        free_command(&command);
        free(line);
    }
    free(line);
}

void minishell_non_interactive_argument(t_env *env, char *line)
{
    t_command_test *command;
	t_ast_node *node;

	node = parse(line);
	command = NULL;
    if (line == NULL)
       return pev("No input provided for non-interactive mode.\n");
    if (node == NULL || node == PARSE_ERROR)
        return pev("parse error\n");
    tree_monitor(node, command, env);
    free_ast_node(node);
    free_command(&command);
}
