#include "../../includes/minishell.h"




char *find_command_in_path(const char *command)
{
    char *env_path;
    char **paths;
    char *full_path;
    int i = 0;

    // Get the PATH environment variable
    env_path = getenv("PATH");
    if (!env_path)
    {
        printf("No PATH environment variable found.\n");
        return NULL;
    }

    // Split the PATH into directories
    paths = ft_split(env_path, ':');
    if (!paths)
    {
        printf("Error splitting PATH.\n");
        return NULL;
    }

    // Iterate through each directory in the PATH
    while (paths[i])
    {
        // Allocate memory for the full path (dir + command)
        full_path = malloc(ft_strlen(paths[i]) + ft_strlen(command) + 2); // +2 for "/" and null terminator
        if (!full_path)
        {
            printf("Memory allocation error.\n");
            return NULL;
        }

        // Build the full path
        ft_strcpy(full_path, paths[i]);
        ft_strcat(full_path, "/"); // Add "/"
        ft_strcat(full_path, command); // Add the command

        // Check if the file exists at this path
        if (access(full_path, F_OK) == 0) // If the file exists, return full path
        {
            free(paths);
            return full_path;
        }

        free(full_path); // Free the allocated memory if not found
        i++;
    }

    // If no valid path found, return NULL
    free(paths);
    return NULL;
}

static void get_path(t_command **command)
{
    t_command *head;
    char **path;
	char *found_path;

    head = (*command);

    while ((*command))
    {
        path = ft_split((*command)->command, ' ');
        if (!path)
            return;
        found_path = find_command_in_path(path[0]);
        if (found_path)
        {
            (*command)->path = found_path;
            printf("Command '%s' found at: %s\n", path[0], found_path);
        }
        else
        {
            (*command)->path = NULL;
            printf("Command '%s' not found in PATH.\n", path[0]);
        }
        (*command) = (*command)->next;
        free(path);
    }
    (*command) = head;
}
static void create_command_list(char *user_prompt, t_command **command)
{
    char **commands;
    t_command *new_node;
    int i = 0;

    if (!user_prompt || !command)
        return;

    commands = ft_split(user_prompt, '|');
    if (!commands)
    {
        perror("Failed to split user prompt");
        return;
    }
    while (commands[i])
    {
        if (commands[i][0] != '\0')
        {
            new_node = create_node(commands[i]);
            if (!new_node)
            {
                perror("Failed to create command node");
                break;
            }
            add_node_back(command, new_node);
        }
        i++;
    }

    i = 0;
    while (commands[i])
    {
        free(commands[i]);
        i++;
    }
    free(commands);
}


void initialise_pipe(t_pipe **pipe, t_command **command, char *user_prompt)
{
	(*pipe)->number_pipe = count_pipe(user_prompt);
	(*pipe)->number_command = (*pipe)->number_pipe + 1;
	create_command_list(user_prompt, command);
	get_path(command);
	print_command_list(*command);
}
