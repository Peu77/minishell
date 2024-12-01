#include "../../includes/minishell.h"

char *find_command_in_path(const char *command)
{
    char *env_path;
    char **paths;
    char *full_path;
    int i = 0;

    env_path = getenv("PATH");
    if (!env_path)
    {
        printf("No PATH environment variable found.\n");
        return NULL;
    }
    paths = ft_split(env_path, ':');
    if (!paths)
    {
        printf("Error splitting PATH.\n");
        return NULL;
    }
    while (paths[i])
    {
        full_path = malloc(ft_strlen(paths[i]) + ft_strlen(command) + 2);
        if (!full_path)
        {
            printf("Memory allocation error.\n");
            return NULL;
        }
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, F_OK) == 0) 
        {
            free(paths);
            return full_path;
        }
        free(full_path); 
        i++;
    }
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
        path = ft_split((*command)->argument, ' ');
        if (!path)
            return;
		((*command)->command_name) = path[0];
        found_path = find_command_in_path((*command)->command_name);
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
	(*pipe)->pid_signal = getpid();
	(*pipe)->number_pipe = count_pipe(user_prompt);
	(*pipe)->number_command = (*pipe)->number_pipe + 1;
	(*pipe)->should_exit = false;
	create_command_list(user_prompt, command);
	get_path(command);
	print_command_list(*command);
}
