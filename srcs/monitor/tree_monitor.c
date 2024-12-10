#include "../../includes/minishell.h"

int tree_monitor(t_ast_node *node, t_command_test *command, char **envp)
{
    if (!node)
        return 0;

    if (node->type == AST_PIPE)
        return pipe_monitor(node, envp);
    if (node->type == AST_AND)
        return and_monitor(node, command, envp);
    if (node->type == AST_OR)
        return or_monitor(node, command, envp);
    if (node->type == AST_COMMAND)
        return command_monitor(node, command, envp);

    return 0;
}
