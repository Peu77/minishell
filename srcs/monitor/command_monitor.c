#include "../../includes/minishell.h"

int command_monitor(t_ast_node *node, t_command_test *command, t_env *env)
{
    t_list* redirect = NULL;

    if (node->redirects)
        redirect = node->redirects;
    transform_node_to_command(node->value, &command, redirect);
    return execution_monitor(command, env);
}
