#include "../../includes/minishell.h"



static void initialize_command_node(t_command *node, char *command_str, char **envp)
{
    if (!node)
        return;

    node->argument = ft_strdup(command_str);
    if (!node->argument)
        return pev("Failed to duplicate command string");
    node->envp = envp;
    node->next = NULL;
    node->previous = NULL;
    node->redirection_token = NULL;
    node->redirection = NULL;
}

t_command *create_node(char *command_str, char **envp)
{
    t_command *new_node;

    if (!command_str)
        return (NULL);

    new_node = malloc(sizeof(t_command));
    if (!new_node)
		return (pe(ERROR_MALLOC), NULL);
    initialize_command_node(new_node, command_str, envp);
    return (new_node);
}

void add_node_back(t_command **head, t_command *new_node)
{
    t_command *current;

    if (!head || !new_node)
        return;
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;
    new_node->previous = current;
}

void print_command_list(t_command *command_list)
{
    t_command *current;

    if (!command_list)
    {
        printf("empty list.\n");
        return;
    }

    current = command_list;
    printf("List of command:\n");
    while (current)
    {
        printf("- Command : %s\n", current->argument);
		printf("- PATH : %s \n", current->path);
        printf("- Command Name : %s\n", current->command_name);
        printf("- Argument : %s\n", current->argument);
        printf("- redirection_token  : %s\n", current->redirection_token);
        current = current->next;
    }
}
