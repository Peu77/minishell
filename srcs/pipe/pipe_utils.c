#include "../../includes/minishell.h"


t_command *create_node(char *command_str)
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

    new_node->command = strdup(command_str);
    if (!new_node->command)
    {
        perror("Failed to duplicate command string");
        free(new_node);
        return (NULL);
    }

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

int count_pipe(char *str)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
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
        printf("- Command : %s\n", current->command);
		printf("- PATH : %s \n", current->path);
        current = current->next;
    }
}
