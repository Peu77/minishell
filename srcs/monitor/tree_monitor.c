#include "../../includes/minishell.h"


int handle_pipe(t_ast_node *node, char **envp)
{
    int pipe_fds[2];
    pid_t left_pid, right_pid;
    int left_status, right_status;

    if (!node->left || !node->right)
        return pe("Invalid pipe node: missing children");
    if (pipe(pipe_fds) == -1)
        return pe("Pipe creation failed");
    if ((left_pid = fork()) == -1)
        return pe("Fork for left process failed");
    if (left_pid == 0)
    {
        close(pipe_fds[0]);
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[1]);
        tree_monitor(node->left, NULL, envp);
        exit(EXIT_SUCCESS);
    }
    if ((right_pid = fork()) == -1)
        return pe("Fork for right process failed");
    if (right_pid == 0)
    {
        close(pipe_fds[1]);
        dup2(pipe_fds[0], STDIN_FILENO);
        close(pipe_fds[0]);
        tree_monitor(node->right, NULL, envp);
        exit(EXIT_SUCCESS);  
    }
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);
    if (WEXITSTATUS(left_status) != 0 || WEXITSTATUS(right_status) != 0)
        return 0;
    return 1;
}


int tree_monitor(t_ast_node *node, t_command_test *command, char **envp)
{
    t_list* redirect = NULL;
    if (!node)
        return (0);

    if (node->type == AST_PIPE)
    {
        int pipe_result = handle_pipe(node, envp);
        return pipe_result;
    }
    else if (node->type == AST_AND)
    {
        int left_result = 0;

        if (node->left)
            left_result = tree_monitor(node->left, command, envp);
		printf ("left result is %d\n", left_result);
        if (left_result && node->right)
            return tree_monitor(node->right, command, envp);
        return (0);
    }
    else if (node->type == AST_COMMAND)
    {
        redirect = (node->redirects) ? node->redirects : NULL;
        transform_node_to_command(node->value, &command, redirect, envp);
        return execution_monitor(command);
    }

    return 0;
}

