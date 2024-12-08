#include "../../includes/minishell.h"

int handle_pipe(t_ast_node *node, char **envp)
{
    int pipe_fds[2];
    pid_t left_pid;
	pid_t right_pid;

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
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);

    return (0);
}

int tree_monitor(t_ast_node *node, t_command_test *command, char **envp)
{
	t_redirect* redirect = NULL;
    if (!node)
        return (0);
    if (node->type == AST_PIPE)
    {
        handle_pipe(node, envp);
        return (0);
    }
    else if (node->type == AST_COMMAND)
    {

		if (node->redirects)
			redirect = (t_redirect *)(node->redirects->content);
		else
    		redirect = NULL;
        transform_node_to_command(node->value, &command, redirect, envp);
        print_command(command);
        execution_monitor(command);
    }
    if (node->left)
        tree_monitor(node->left, command, envp);
    if (node->right)
        tree_monitor(node->right, command, envp);
    return (0);
}
