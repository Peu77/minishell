#include "../../includes/minishell.h"


t_command *create_node(char *command_str, char **envp)
{
    t_command *new_node;

    if (!command_str)
        return (NULL);

    new_node = malloc(sizeof(t_command));
    if (!new_node)
    {
        perror("Failed to allocate memory for command node");
        return (NULL);
    }

    new_node->argument = strdup(command_str);
    if (!new_node->argument)
    {
        perror("Failed to duplicate command string");
        free(new_node);
        return (NULL);
    }
	new_node->envp = envp;
    new_node->next = NULL;
    new_node->previous = NULL;

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
        current = current->next;
    }
}
