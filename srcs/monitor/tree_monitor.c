#include "../../includes/minishell.h"

int tree_monitor(t_ast_node *node, t_command_test *command)
{
    if (!node)
        return (0);
    if (tree_monitor(node->left, command) != 0)
        return (1);
    if (node->type == AST_COMMAND)
	{
		transform_node_to_command(node->value, &command);
		print_command(command);
	}
    if (tree_monitor(node->right, command) != 0)
        return (1);

    return (0);
}
