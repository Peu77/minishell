#include "../../includes/minishell.h"

int tree_monitor(t_ast_node *node, t_command_test *command, char **envp)
{
    if (!node)
        return (0);
    if (tree_monitor(node->left, command, envp) != 0)
        return (1);
    if (node->type == AST_COMMAND)
	{
		transform_node_to_command(node->value, &command, envp);
		print_command(command);
		execution_monitor(command);
	}
    if (tree_monitor(node->right, command, envp) != 0)
        return (1);
    return (0);
}
