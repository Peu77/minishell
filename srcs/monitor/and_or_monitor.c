#include "../../includes/minishell.h"

int and_monitor(t_ast_node *node, t_command_test *command, char **envp, t_env *env)
{
    int left_result = 0;
    
    if (node->left)
        left_result = tree_monitor(node->left, command, envp, env);
    if (!left_result && node->right)
        return tree_monitor(node->right, command, envp, env);
    
    return left_result;
}

int or_monitor(t_ast_node *node, t_command_test *command, char **envp, t_env *env)
{
    int left_result = 0;

    if (node->left)
        left_result = tree_monitor(node->left, command, envp, env);
    if (left_result && node->right)
        return tree_monitor(node->right, command, envp, env);
    
    return left_result;
}
